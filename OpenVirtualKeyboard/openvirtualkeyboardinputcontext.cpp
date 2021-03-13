#include <QDateTime>
#include <QInputMethodEvent>
#include <QGuiApplication>
#include <QString>
#include <QStringList>
#include <QQuickItem>
#include <QScopeGuard>
#include "openvirtualkeyboardinputcontext.h"
#include "keyboardcreator.h"
#include "injectedkeyboardpositioner.h"
#include "keyboardwindowpositioner.h"
#include "keypressinterceptor.h"
#include "key.h"
#include "utils.h"

OpenVirtualKeyboardInputContext::OpenVirtualKeyboardInputContext( const QStringList& params )
{
    const bool animated    = params.contains( QStringLiteral("animateRollout"), Qt::CaseInsensitive );
    const bool inOwnWindow = params.contains( QStringLiteral("ownWindow"), Qt::CaseInsensitive );

    _keyboardComponentUrl = inOwnWindow ? QUrl( "qrc:///ovk/qml/KeyboardWindow.qml" )
                                        : QUrl( "qrc:///ovk/qml/Keyboard.qml" );

    _layoutsProvider.reset( new KeyboardLayoutsProvider );

    if (params.contains( QStringLiteral("immediateLoading"), Qt::CaseInsensitive ))
        loadKeyboard();

    _positioner.reset( createPositioner( inOwnWindow ));
    _positioner->enableAnimation( animated );

    connect( qGuiApp, &QGuiApplication::applicationStateChanged, this, []( Qt::ApplicationState s ){
        if (s == Qt::ApplicationInactive)
            qGuiApp->inputMethod()->hide();
    });
}

OpenVirtualKeyboardInputContext::~OpenVirtualKeyboardInputContext() = default;

bool OpenVirtualKeyboardInputContext::isValid() const
{
    return true;
}

void OpenVirtualKeyboardInputContext::setFocusObject( QObject* object )
{
    _focusObject = object;
    _positioner->updateFocusItem( imEnabledFocusItem() );
    setupTextChangedListener();
    updateEnterKeyAction();
    updateInputMethodHints();
}

bool OpenVirtualKeyboardInputContext::isAnimating() const
{
    return _positioner->isAnimating();
}

void OpenVirtualKeyboardInputContext::showInputPanel()
{
    if (_keyboardCreated) {
        updateInputMethodHints();
        show();
    } else {
        loadKeyboard();
    }
}

void OpenVirtualKeyboardInputContext::hideInputPanel()
{
    _visible = false;
    _positioner->hide();
    emitInputPanelVisibleChanged();
    setLayoutType( KeyboardLayoutType::Alphabet );
    setShiftOn( false );
    setShiftLocked( false );
}

bool OpenVirtualKeyboardInputContext::isInputPanelVisible() const
{
    return _visible;
}

bool OpenVirtualKeyboardInputContext::shiftOn() const
{
    return _shiftOn;
}

bool OpenVirtualKeyboardInputContext::shiftLocked() const
{
    return _shiftLocked;
}

KeyboardLayoutType::Type OpenVirtualKeyboardInputContext::layoutType() const
{
    return _layoutType;
}

bool OpenVirtualKeyboardInputContext::enterKeyActionEnabled() const
{
    return _enterKeyActionEnabled;
}

Qt::EnterKeyType OpenVirtualKeyboardInputContext::enterKeyAction() const
{
    return _enterKeyAction;
}

KeyboardLayoutsProvider* OpenVirtualKeyboardInputContext::layoutProvider() const
{
    return _layoutsProvider.get();
}

void OpenVirtualKeyboardInputContext::onKeyClicked( Key* key )
{
    if (!key)
        return;

    switch ( key->type() ) {
        case Key::KeyDefault:
            handleKeyClicked( key->text() );
            break;
        case Key::Space:
            handleKeyClicked( QStringLiteral( " " ));
            break;
        case Key::Backspace:
            handleBackspace();
            break;
        case Key::Shift:
            handleShiftKey();
            break;
        case Key::Enter:
            handleEnter();
            break;
        case Key::Symbol:
            handleSymbolKey();
            break;
        case Key::NextPage:
            _layoutsProvider->incrementPageForLayoutType( _layoutType );
            break;
        case Key::Hide:
            QGuiApplication::inputMethod()->hide();
            break;
        case Key::Language:
            // noop, this is handled via QML
            break;
    }
}

void OpenVirtualKeyboardInputContext::onAlternativeSelected()
{
    const auto character = _positioner->selectedAlternative();
    if (!character.isEmpty())
        handleKeyClicked( character );
}

void OpenVirtualKeyboardInputContext::setupTextChangedListener()
{
    static QMetaObject::Connection connection{};

    // as first try to discard connection to previously connected focus object
    QObject::disconnect( connection );

    auto item = imEnabledFocusItem();
    if (!item)
        return;

    const auto text = item->property( "text" );
    if (!text.isValid())
        return;

    auto mo = item->metaObject();
    int index = metaObject()->indexOfMethod( "onTextChanged()" );
    connection = connect( item,
                          mo->property( mo->indexOfProperty( "text" )).notifySignal(),
                          this,
                          metaObject()->method( index ));
}

bool OpenVirtualKeyboardInputContext::shiftEnabled() const
{
    return _shiftEnabled;
}

void OpenVirtualKeyboardInputContext::setShiftOn( bool shiftOn )
{
    if (_shiftOn == shiftOn)
        return;

    _shiftOn = shiftOn;
    emit shiftOnChanged();
}

void OpenVirtualKeyboardInputContext::setShiftLocked( bool shiftLocked )
{
    if (_shiftLocked == shiftLocked)
        return;

    _shiftLocked = shiftLocked;
    emit shiftLockedChanged();
}

void OpenVirtualKeyboardInputContext::handleKeyClicked( const QString& character )
{
    if (!_focusObject)
        return;

    QInputMethodEvent event;
    event.setCommitString( character );
    QGuiApplication::sendEvent( _focusObject, &event );
}

void OpenVirtualKeyboardInputContext::onShiftLocked()
{
    if (_shiftLocked) {
        setShiftLocked( false );
        setShiftOn( false );
    } else if (_shiftOn) {
        setShiftLocked( true );
    } else {
        setShiftLocked( true );
        setShiftOn( true );
    }
}

void OpenVirtualKeyboardInputContext::informKeyboardCreated()
{
    _keyboardCreated = true;
}

void OpenVirtualKeyboardInputContext::setLayoutType( KeyboardLayoutType::Type layoutType )
{
    if (_layoutType == layoutType)
        return;

    _layoutType = layoutType;
    emit layoutTypeChanged();
}

void OpenVirtualKeyboardInputContext::setEnterKeyActionEnabled( bool enterActionEnabled )
{
    if (_enterKeyActionEnabled == enterActionEnabled)
        return;

    _enterKeyActionEnabled = enterActionEnabled;
    emit enterKeyActionEnabledChanged();
}

void OpenVirtualKeyboardInputContext::setEnterKeyAction( Qt::EnterKeyType type )
{
    if (_enterKeyAction == type)
        return;

    _enterKeyAction = type;
    emit enterKeyActionChanged();
}

void OpenVirtualKeyboardInputContext::setShiftEnabled( bool shiftEnabled )
{
    if (_shiftEnabled == shiftEnabled)
        return;

    _shiftEnabled = shiftEnabled;
    emit shiftEnabledChanged();
}

void OpenVirtualKeyboardInputContext::onFocusItemEnterKeyActionChanged()
{
    bool dummy;
    setEnterKeyAction( static_cast<Qt::EnterKeyType>(
        ovk::propertyValue<int>( _focusObject, "enterKeyAction", Qt::EnterKeyDefault, dummy )));
}

void OpenVirtualKeyboardInputContext::onFocusItemEnterKeyActionEnabledChanged()
{
    bool dummy;
    setEnterKeyActionEnabled(
                ovk::propertyValue( _focusObject, "enterKeyActionEnabled", true, dummy ));
}

void OpenVirtualKeyboardInputContext::onTextChanged()
{
    if (!_shiftLocked)
        setShiftOn( isShiftRequiredByAutoUppercase() );
}

void OpenVirtualKeyboardInputContext::show()
{
    _visible = true;
    _positioner->show();
    emitInputPanelVisibleChanged();
}

void OpenVirtualKeyboardInputContext::updateEnterKeyAction()
{
    static QMetaObject::Connection enterKeyActionConnection{};
    static QMetaObject::Connection enterKeyActionEnabledConnection{};

    // as first try to discard connection to previously connected focus object
    QObject::disconnect( enterKeyActionConnection );
    QObject::disconnect( enterKeyActionEnabledConnection );

    auto item = imEnabledFocusItem();
    bool valid = false;
    setEnterKeyAction( static_cast<Qt::EnterKeyType>(
        ovk::propertyValue<int>( item, "enterKeyAction", Qt::EnterKeyDefault, valid )));

    if (valid)
        enterKeyActionConnection = connect( item,
                                            enterKeyActionChangedSignal( item ),
                                            this,
                                            enterKeyActionChangedSlot() );

    setEnterKeyActionEnabled( ovk::propertyValue( item, "enterKeyActionEnabled", true, valid ));

    if (valid)
        enterKeyActionEnabledConnection = connect( item,
                                                   enterKeyActionEnabledChangedSignal( item ),
                                                   this,
                                                   enterKeyActionEnabledChangedSlot() );
}

QMetaMethod
OpenVirtualKeyboardInputContext::enterKeyActionChangedSignal( QObject* object ) const
{
    if (!object)
        return QMetaMethod{};
    auto mo = object->metaObject();
    return mo->property( mo->indexOfProperty( "enterKeyAction" )).notifySignal();
}

QMetaMethod OpenVirtualKeyboardInputContext::enterKeyActionChangedSlot() const
{
    int index = metaObject()->indexOfMethod( "onFocusItemEnterKeyActionChanged()" );
    return metaObject()->method( index );
}

QMetaMethod
OpenVirtualKeyboardInputContext::enterKeyActionEnabledChangedSignal( QObject* object ) const
{
    if (!object)
        return QMetaMethod{};
    auto mo = object->metaObject();
    return mo->property( mo->indexOfProperty( "enterKeyActionEnabled" )).notifySignal();
}

QMetaMethod OpenVirtualKeyboardInputContext::enterKeyActionEnabledChangedSlot() const
{
    int index = metaObject()->indexOfMethod( "onFocusItemEnterKeyActionEnabledChanged()" );
    return metaObject()->method( index );
}

void OpenVirtualKeyboardInputContext::updateInputMethodHints()
{
    using namespace KeyboardLayoutType;

    Type layout = Alphabet;
    bool shiftOn = false;
    bool shiftLock = false;
    bool shiftEnabled = true;
    auto layoutSetter = qScopeGuard( [&, this] {
        setLayoutType( layout );
        setShiftOn( shiftOn );
        setShiftLocked( shiftLock );
        setShiftEnabled( shiftEnabled );
    });

    auto imEnabledItem = imEnabledFocusItem();
    if (!imEnabledItem)
        return;

    const int  hints       = imEnabledItem->inputMethodQuery( Qt::ImHints ).toInt();
    const auto layoutHints = static_cast<Type>( hints );

    shiftOn      = layoutHints & ( Qt::ImhPreferUppercase | Qt::ImhUppercaseOnly );
    shiftLock    = layoutHints & Qt::ImhUppercaseOnly;
    shiftEnabled = !shiftLock;

    if (!shiftOn && isShiftRequiredByAutoUppercase( hints ))
        shiftOn = true;

    if ((layout = static_cast<Type>( layoutHints & Dial ))) return;
    if ((layout = static_cast<Type>( layoutHints & Digits ))) return;
    if ((layout = static_cast<Type>( layoutHints & Numbers ))) return;
    if (( layoutHints & Qt::ImhDate ) || ( layoutHints & Qt::ImhTime )) {
        layout = Symbols;
        return;
    }
    layout = Alphabet; // no match => let's go default
}

bool OpenVirtualKeyboardInputContext::isShiftRequiredByAutoUppercase() const
{
    if (!_focusObject)
        return false;

    auto imEnabledItem = imEnabledFocusItem();
    if (!imEnabledItem)
        return false;

    return isShiftRequiredByAutoUppercase( imEnabledItem->inputMethodQuery( Qt::ImHints ).toInt() );
}

bool OpenVirtualKeyboardInputContext::isShiftRequiredByAutoUppercase( int hints ) const
{
    if (hints & Qt::ImhNoAutoUppercase)
        return false;

    const auto text = _focusObject->property( "text" ).toString();

    if (!text.isEmpty() && !text.endsWith( ' ' ))
        return false;

    for (auto it = text.crbegin(); it != text.crend(); ++it) {
        if (*it == '.')
            return true;
        if (*it != ' ')
            return false;
    }

    return true;
}

QQuickItem* OpenVirtualKeyboardInputContext::imEnabledFocusItem() const
{
    if (!_focusObject)
        return nullptr;

    auto quickItem = qobject_cast<QQuickItem*>( _focusObject );
    if (!quickItem)
        return nullptr;

    if (!quickItem->inputMethodQuery( Qt::ImEnabled ).toBool())
        return nullptr;

    return quickItem;
}

void OpenVirtualKeyboardInputContext::loadKeyboard()
{
    if (!_keyboardCreator) {
        _keyboardCreator.reset( new KeyboardCreator( _keyboardComponentUrl ));

        connect( _keyboardCreator.get(), &KeyboardCreator::created, this, [this] {
            _positioner->setKeyboardObject( _keyboardCreator->keyboardObject() );

            connect( _positioner.get(),
                     &InjectedKeyboardPositioner::animatingChanged,
                     this,
                     &OpenVirtualKeyboardInputContext::emitAnimatingChanged );
            connect( _keyboardCreator->keyPressInterceptor(),
                     &KeyPressInterceptor::keyClicked,
                     this,
                     &OpenVirtualKeyboardInputContext::onKeyClicked );
            connect( _keyboardCreator->keyPressInterceptor(),
                     &KeyPressInterceptor::keyRepeatClicked,
                     this,
                     &OpenVirtualKeyboardInputContext::onKeyClicked );
            connect( _keyboardCreator->keyPressInterceptor(),
                     &KeyPressInterceptor::alternativeSelected,
                     this,
                     &OpenVirtualKeyboardInputContext::onAlternativeSelected );
            connect( _keyboardCreator->keyPressInterceptor(),
                     &KeyPressInterceptor::shiftLocked,
                     this,
                     &OpenVirtualKeyboardInputContext::onShiftLocked );

            if (imEnabledFocusItem())
                show();
        } );
    }

    _keyboardCreator->createKeyboard();
}

void OpenVirtualKeyboardInputContext::handleEnter()
{
    if (!_focusObject)
        return;

    auto pressEvent = new QKeyEvent( QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier );
    QGuiApplication::postEvent( _focusObject, pressEvent );
    auto releaseEvent = new QKeyEvent( QEvent::KeyRelease, Qt::Key_Enter, Qt::NoModifier );
    QGuiApplication::postEvent( _focusObject, releaseEvent );
}

void OpenVirtualKeyboardInputContext::handleShiftKey()
{
    if (_shiftOn) {
        if (isShiftDoubleClicked()) {
            setShiftLocked( !_shiftLocked );
            setShiftOn( _shiftLocked );
        } else {
            setShiftLocked( false );
            setShiftOn( false );
        }
    } else {
        setShiftOn( true );
        updateLastShiftClick();
    }
}

void OpenVirtualKeyboardInputContext::handleSymbolKey()
{
    if (_layoutType == KeyboardLayoutType::Symbols) {
        updateInputMethodHints();

        // If we resolved Symbols from hints, but Symbols
        // is already set, we force Alphabet
        if (_layoutType == KeyboardLayoutType::Symbols)
            setLayoutType( KeyboardLayoutType::Alphabet );
    } else {
        setLayoutType( KeyboardLayoutType::Symbols );
    }
}

void OpenVirtualKeyboardInputContext::handleBackspace()
{
    if (!_focusObject)
        return;

    QInputMethodEvent event;
    event.setCommitString( "", -1, 1 );
    QGuiApplication::sendEvent( _focusObject, &event );
}

qint64 OpenVirtualKeyboardInputContext::updateLastShiftClick() const
{
    static qint64 sLastClick = 0;
    quint64 lastClick = sLastClick;
    sLastClick = QDateTime::currentMSecsSinceEpoch();
    return lastClick;
}

bool OpenVirtualKeyboardInputContext::isShiftDoubleClicked() const
{
    auto lastClick = updateLastShiftClick();
    quint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    bool isDoubleClicked = (currentTime - lastClick) < 500;
    return isDoubleClicked;
}

AbstractPositioner* OpenVirtualKeyboardInputContext::createPositioner( bool inOwnWindow ) const
{
    if (inOwnWindow)
        return new KeyboardWindowPositioner;
    return new InjectedKeyboardPositioner;
}
