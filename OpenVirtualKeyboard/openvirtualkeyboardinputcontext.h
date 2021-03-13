#ifndef OPENVIRTUALKEYBOARDINPUTCONTEXT_H
#define OPENVIRTUALKEYBOARDINPUTCONTEXT_H

#include <memory>
#include <qpa/qplatforminputcontext.h>
#include <QPointer>
#include <QUrl>
#include "keyboardlayouttype.h"
#include "keyboardlayoutsprovider.h"

class QQuickItem;
class QStringList;
class KeyboardCreator;
class Key;
class AbstractPositioner;

class OpenVirtualKeyboardInputContext : public QPlatformInputContext
{
    Q_OBJECT
    Q_PROPERTY(bool shiftOn READ shiftOn WRITE setShiftOn NOTIFY shiftOnChanged)
    Q_PROPERTY(bool shiftLocked READ shiftLocked WRITE setShiftLocked NOTIFY shiftLockedChanged)
    Q_PROPERTY(bool shiftEnabled READ shiftEnabled WRITE setShiftEnabled NOTIFY shiftEnabledChanged)
    Q_PROPERTY(KeyboardLayoutType::Type layoutType READ layoutType WRITE setLayoutType
               NOTIFY layoutTypeChanged)
    Q_PROPERTY(bool enterKeyActionEnabled READ enterKeyActionEnabled
               WRITE setEnterKeyActionEnabled NOTIFY enterKeyActionEnabledChanged)
    Q_PROPERTY(Qt::EnterKeyType enterKeyAction READ enterKeyAction WRITE setEnterKeyAction
               NOTIFY enterKeyActionChanged)
    Q_PROPERTY(KeyboardLayoutsProvider* layoutProvider READ layoutProvider
               NOTIFY layoutProviderChanged)
public:
    OpenVirtualKeyboardInputContext( const QStringList& params );
    ~OpenVirtualKeyboardInputContext() override;

    bool isValid() const override;
    void setFocusObject( QObject* object ) override;
    bool isAnimating() const override;

    void showInputPanel() override;
    void hideInputPanel() override;
    bool isInputPanelVisible() const override;

    bool shiftOn() const;
    bool shiftLocked() const;
    bool shiftEnabled() const;
    KeyboardLayoutType::Type layoutType() const;
    bool enterKeyActionEnabled() const;
    Qt::EnterKeyType enterKeyAction() const;
    KeyboardLayoutsProvider* layoutProvider() const;

signals:
    void shiftOnChanged();
    void shiftLockedChanged();
    void shiftEnabledChanged();
    void layoutTypeChanged();
    void enterKeyActionEnabledChanged();
    void enterKeyActionChanged();
    void layoutProviderChanged();

public slots:
    void setShiftOn( bool shiftOn );
    void setShiftLocked( bool shiftLocked );
    void setShiftEnabled( bool shiftEnabled );
    void onShiftLocked();
    void informKeyboardCreated();
    void setLayoutType( KeyboardLayoutType::Type layoutType );
    void setEnterKeyActionEnabled( bool enterActionEnabled );
    void setEnterKeyAction( Qt::EnterKeyType type );

private slots:
    void onFocusItemEnterKeyActionChanged();
    void onFocusItemEnterKeyActionEnabledChanged();
    void onTextChanged();

private:
    void show();
    void onKeyClicked( Key* key );
    void onAlternativeSelected();
    void setupTextChangedListener();
    void updateEnterKeyAction();
    QMetaMethod enterKeyActionChangedSignal( QObject* object ) const;
    QMetaMethod enterKeyActionChangedSlot() const;
    QMetaMethod enterKeyActionEnabledChangedSignal( QObject* object ) const;
    QMetaMethod enterKeyActionEnabledChangedSlot() const;
    void updateInputMethodHints();
    bool isShiftRequiredByAutoUppercase() const;
    bool isShiftRequiredByAutoUppercase( int hints ) const;
    QQuickItem* imEnabledFocusItem() const;
    void loadKeyboard();
    void handleKeyClicked( const QString& character );
    void handleEnter();
    void handleShiftKey();
    void handleSymbolKey();
    void handleBackspace();
    qint64 updateLastShiftClick() const;
    bool isShiftDoubleClicked() const;
    AbstractPositioner* createPositioner( bool inOwnWindow ) const;

    QUrl                                     _keyboardComponentUrl;
    std::unique_ptr<KeyboardLayoutsProvider> _layoutsProvider;
    std::unique_ptr<KeyboardCreator>         _keyboardCreator;
    std::unique_ptr<AbstractPositioner>      _positioner;
    QPointer<QObject>                        _focusObject           = nullptr;
    bool                                     _visible               = false;
    bool                                     _shiftOn               = false;
    bool                                     _shiftLocked           = false;
    bool                                     _shiftEnabled          = true;
    bool                                     _keyboardCreated       = false;
    KeyboardLayoutType::Type                 _layoutType            = KeyboardLayoutType::Alphabet;
    bool                                     _enterKeyActionEnabled = false;
    Qt::EnterKeyType                         _enterKeyAction        = Qt::EnterKeyDefault;
};

#endif // OPENVIRTUALKEYBOARDINPUTCONTEXT_H
