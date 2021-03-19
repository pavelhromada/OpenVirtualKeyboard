/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#include "keyboardwindowpositioner.h"
#include <QGuiApplication>
#include <QQuickWindow>
#include <QPropertyAnimation>
#include <QTimer>
#include <QQuickItem>
#include <QScreen>
#include <QDebug>
#include "loggingcategory.h"
#include "keypreview.h"
#include "keyalternativespreview.h"

KeyboardWindowPositioner::~KeyboardWindowPositioner() = default;

void KeyboardWindowPositioner::setKeyboardObject( QObject* keyboardObject )
{
    _keyboardWindow = qobject_cast<QQuickWindow*>( keyboardObject );
    if (!_keyboardWindow) {
        qCWarning(logOvk) << "Couldn't cast keyboard object to QQuickWindow";
        return;
    }

    _keyboard = _keyboardWindow->findChild<QQuickItem*>( "keyboard" );

    init( _keyboard );
    initKeyboardWindow();
}

void KeyboardWindowPositioner::enableAnimation( bool enabled )
{
    if (enabled) {
        _animation.reset( new QPropertyAnimation );
        _animation->setPropertyName( "y" );
        _animation->setEasingCurve( QEasingCurve( QEasingCurve::OutCubic ));

        connect( _animation.get(),
                 &QAbstractAnimation::stateChanged,
                 this,
                 &AbstractPositioner::animatingChanged );
        connect( _animation.get(),
                 &QAbstractAnimation::finished,
                 this,
                 &KeyboardWindowPositioner::onAnimationFinished );
    } else {
        _animation.reset();
    }
}

void KeyboardWindowPositioner::updateFocusItem( QQuickItem* focusItem )
{
    _focusItem = focusItem;
    observeWindowOfFocusedItem();
}

void KeyboardWindowPositioner::show()
{
    // We send the call through event loop because Qt's input method context
    // called setFocusObject() and showInputPanel() in wrong order (for our purposes)
    // and this way we walked around some UI imperfect behaviour.

    QTimer::singleShot( 0, this, [this] {
        if (!_keyboardWindow || !_focusItem || !_keyboard) {
            _shown = false;
            return;
        }

        bool alreadyShown = _shown;
        _shown            = true;

        if (alreadyShown)
            return;

        const auto screen = _focusItem->window()->screen();
        if (!screen)
            return;

        const auto geometry = screen->geometry();

        // Note: height + 1 pixel as a work around, because of odd behaviour when
        // transparent area of keyboard window was rendered as black.
        _keyboardWindow->setGeometry(
            geometry.x(), _keyboard->height(), geometry.width(), geometry.height() + 1 );
        _keyboardWindow->show();

        if ( _animation ) {
            _animation->setStartValue( _keyboard->height() );
            _animation->setEndValue( 0 );
            _animation->start();
        } else {
            _keyboardWindow->setY( 0 );
        }
    });
}

void KeyboardWindowPositioner::hide()
{
    hide( false );
}

void KeyboardWindowPositioner::hide( bool suppressAnimation )
{
    _shown = false;

    if (!_keyboardWindow || !_keyboard)
        return;

    if (_animation && !suppressAnimation) {
        _animation->setStartValue( 0 );
        _animation->setEndValue( _keyboard->height() );
        _animation->start();
    } else {
        _keyboardWindow->setY( _keyboard->height() );
        _keyboardWindow->hide();
    }
}

bool KeyboardWindowPositioner::isAnimating() const
{
    return _animation ? _animation->state() == QAbstractAnimation::Running : false;
}

void KeyboardWindowPositioner::initKeyboardWindow()
{
    if (!_keyboardWindow)
        return;

    const auto flags = QGuiApplication::platformName() == QLatin1String("xcb")
        ? ( Qt::Window | Qt::BypassWindowManagerHint )
        : Qt::Tool;

    _keyboardWindow->setFlags( _keyboardWindow->flags() | flags );

    setupKeyboardWindowMask();

    const auto appWindow = QGuiApplication::focusWindow();
    const auto screen = appWindow ? appWindow->screen() : nullptr;

    if (screen) {
        const auto geometry = screen->geometry();
        // Note: height + 1 pixel as a work around, because of odd behaviour when
        // transparent area of keyboard window was rendered as black.
        _keyboardWindow->setGeometry(
            geometry.x(), _keyboard->height(), geometry.width(), geometry.height() + 1 );
    }

    _keyboardWindow->setVisible( false );
    observeWindowOfFocusedItem();

    if (_animation)
        _animation->setTargetObject( _keyboardWindow );
}

void KeyboardWindowPositioner::setupKeyboardWindowMask()
{
    connect( _keyboard, &QQuickItem::heightChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyboard, &QQuickItem::widthChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyPreview, &QQuickItem::heightChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyPreview, &QQuickItem::widthChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyPreview, &QQuickItem::xChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyPreview, &QQuickItem::yChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyPreview, &QQuickItem::visibleChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyAlternatives, &QQuickItem::heightChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyAlternatives, &QQuickItem::widthChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyAlternatives, &QQuickItem::xChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyAlternatives, &QQuickItem::yChanged, this, &KeyboardWindowPositioner::updateMask );
    connect( _keyAlternatives, &QQuickItem::visibleChanged, this, &KeyboardWindowPositioner::updateMask );

    updateMask();
}

void KeyboardWindowPositioner::observeWindowOfFocusedItem()
{
    static QMetaObject::Connection screenChangedConnection{};
    static QMetaObject::Connection visibleChangedConnection{};

    // as first try to discard connection to previously connected focus object
    QObject::disconnect( screenChangedConnection );
    QObject::disconnect( visibleChangedConnection );

    if (!_focusItem)
        return;

    auto window = _focusItem ? _focusItem->window() : QGuiApplication::focusWindow();

    if (window) {
        screenChangedConnection = connect( window,
                                           &QQuickWindow::screenChanged,
                                           this,
                                           &KeyboardWindowPositioner::onScreenChanged );
        visibleChangedConnection = connect( window,
                                            &QQuickWindow::visibleChanged,
                                            this,
                                            &KeyboardWindowPositioner::onWindowVisibleChanged );
    }
}

void KeyboardWindowPositioner::updateMask()
{
    if (!_keyboard || !_keyboardWindow)
        return;

    QRegion mask( _keyboard->x(), _keyboard->y(), _keyboard->width(), _keyboard->height() );

    const auto content = _keyboardWindow->contentItem();

    if (_keyPreview && _keyPreview->isVisible()) {
        const auto topLeft = content->mapFromItem( _keyPreview, QPointF( 0, 0 ));
        mask += QRect( topLeft.x(), topLeft.y(), _keyPreview->width(), _keyPreview->height() );
    }

    if (_keyAlternatives && _keyAlternatives->isVisible()) {
        const auto topLeft = content->mapFromItem( _keyAlternatives, QPointF( 0, 0 ));
        mask += QRect(
            topLeft.x(), topLeft.y(), _keyAlternatives->width(), _keyAlternatives->height() );
    }

    _keyboardWindow->setMask( mask );
}

void KeyboardWindowPositioner::onAnimationFinished()
{
    if (!_shown)
        _keyboardWindow->hide();
}

void KeyboardWindowPositioner::onScreenChanged( QScreen* screen )
{
    if (!screen || !_keyboardWindow)// || !_keyboardWindow->isVisible())
        return;

    const auto geometry = screen->geometry();
    _keyboardWindow->setGeometry( geometry.x(), 0, geometry.width(), geometry.height() + 1 );
}

void KeyboardWindowPositioner::onWindowVisibleChanged( bool visible )
{
    if (!visible && _shown)
        hide( true ); // suppress animation to allow application properly close
}
