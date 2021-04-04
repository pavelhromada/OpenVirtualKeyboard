/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#include "injectedkeyboardpositioner.h"
#include <chrono>
#include <QGuiApplication>
#include <QQuickItem>
#include <QQuickWindow>
#include <QTimer>

InjectedKeyboardPositioner::InjectedKeyboardPositioner( bool noContentScroll )
    : _scrollContentItem( !noContentScroll )
{ }

InjectedKeyboardPositioner::~InjectedKeyboardPositioner() = default;

void InjectedKeyboardPositioner::setKeyboardObject( QObject* keyboardObject )
{
    _keyboard = qobject_cast<QQuickItem*>( keyboardObject );
    if (!_keyboard)
        return;

    init( _keyboard );

    connect( _keyboard,
             &QQuickItem::heightChanged,
             this,
             &InjectedKeyboardPositioner::onHeightChanged );

    updateFocusItem( _focusItem );

    if (_contentItem)
        _keyboard->setY( _contentItem->height() );

    connect( qGuiApp,
             &QGuiApplication::applicationStateChanged,
             this,
             &InjectedKeyboardPositioner::onApplicationStateChanged );
    onApplicationStateChanged( qGuiApp->applicationState() );
}

void InjectedKeyboardPositioner::enableAnimation( bool enabled )
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
                 &InjectedKeyboardPositioner::onAnimationFinished );
    } else {
        _animation.reset();
    }
}

void InjectedKeyboardPositioner::updateFocusItem( QQuickItem* focusItem )
{
    if (_focusItem != focusItem)
        _focusItemChanged = true;

    _focusItem = focusItem;
    if (!_focusItem || !_keyboard)
        return;

    auto window      = _focusItem->window();
    auto contentItem = window ? window->contentItem() : nullptr;

    if (contentItem == _contentItem)
        return;

    if (_contentItem)
        _contentItem->disconnect( this );

    _contentItem = contentItem;
    _keyboard->setParentItem( _contentItem );
    connect( _contentItem,
             &QQuickItem::heightChanged,
             this,
             &InjectedKeyboardPositioner::onHeightChanged );

}

void InjectedKeyboardPositioner::show()
{
    // We send the call through event loop because Qt's input method context
    // called setFocusObject() and showInputPanel() in wrong order (for our purposes)
    // and this way we walked around some UI imperfect behaviour.

    std::chrono::milliseconds milliseconds( _animation ? _appStateReactivated ? 100 : 0 : 0 );

    QTimer::singleShot( milliseconds, this, [this] {
        if (!_keyboard || !_contentItem) {
            _shown = false;
            return;
        }

        bool alreadyShown = _shown;
        _shown            = true;

        if (alreadyShown) {
            if (_focusItemChanged) {
                updateContentItemPosition( true );
                _focusItemChanged = false;
            }
            return;
        }

        _focusItemChanged = false;
        updateContentItemPosition( true );

        if (_animation) {
            _animation->setTargetObject( nullptr );
            _animation->setStartValue( _contentItem->height() + _offset );
            _animation->setEndValue( _contentItem->height() - _keyboard->height() + _offset );
            _animation->setTargetObject( _keyboard );
            _animation->start();
        } else {
            _keyboard->setY( _contentItem->height() - _keyboard->height() + _offset );
        }
    } );
}

void InjectedKeyboardPositioner::hide()
{
    _shown = false;

    if (!_keyboard || !_contentItem)
        return;

    if (_animation) {
        _animation->setTargetObject( nullptr );
        _animation->setStartValue( _keyboard->y() );
        _animation->setEndValue( _keyboard->y() + _keyboard->height() );
        _animation->setTargetObject( _keyboard );
        _animation->start();
    } else {
        _contentItem->setY( 0 );
        _keyboard->setY( _contentItem->height() );
    }
}

bool InjectedKeyboardPositioner::isAnimating() const
{
    return _animation ? _animation->state() == QAbstractAnimation::Running : false;
}

void InjectedKeyboardPositioner::updateContentItemPosition( bool updateKeyboardPosition )
{
    if (!_keyboard || !_contentItem || !_focusItem)
        return;

    if (!_shown)
        _keyboard->setVisible( false );

    auto focusItemBottom = _contentItem->mapFromItem( _focusItem, QPointF( 0, 0 )).y()
        + _focusItem->height() + 5; // count with 5px spacing
    auto keyboardTop = _contentItem->height() - _keyboard->height();
    _offset = _scrollContentItem
                 ? focusItemBottom > keyboardTop ? focusItemBottom - keyboardTop : 0
                 : 0;
    _contentItem->setY( -_offset );
    if (updateKeyboardPosition)
        _keyboard->setY(( _shown ? keyboardTop : _contentItem->height() ) + _offset );
    _keyboard->setVisible( true );
}

void InjectedKeyboardPositioner::onHeightChanged()
{
    if (!_keyboard || !_contentItem)
        return;

    if (_shown)
        updateContentItemPosition( true );
    else
        _keyboard->setY( _contentItem->height() + _offset );
}

void InjectedKeyboardPositioner::onApplicationStateChanged( Qt::ApplicationState s )
{
    static bool wasAlreadyActive = false;

    if (s == Qt::ApplicationActive) {
        if (wasAlreadyActive)
            _appStateReactivated = true;
        wasAlreadyActive = true;
    } else if (s == Qt::ApplicationInactive)
        qGuiApp->inputMethod()->hide();
}

void InjectedKeyboardPositioner::onAnimationFinished()
{
    _appStateReactivated = false;

    if (!_shown) {
        _contentItem->setY( 0 );
        _keyboard->setY( _contentItem->height() );
    }
}
