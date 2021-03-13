#include <QUrl>
#include <QQmlEngine>
#include "openvirtualkeyboardinputcontext.h"
#include "openvirtualkeyboardplugin.h"
//#include "keyboardlayoutloader.h"
#include "keyboardstyle.h"
#include "keyalternativespreview.h"
#include "keypreview.h"
#include "keypressinterceptor.h"
#include "key.h"
#include "keyboardlayouttype.h"
#include "keyboardlayoutmodel.h"
#include "keyboardlayoutsprovider.h"
#include "loggingcategory.h"

Q_LOGGING_CATEGORY(logOvk, "openvirtualkeyboard", QtFatalMsg)

static QObject* gInputContext = nullptr;

static QObject* inputContextProvider( QQmlEngine* /*engine*/, QJSEngine* /*scriptEngine*/ )
{
    return gInputContext;
}

QPlatformInputContext* OpenVirtualKeyboardPlugin::create( const QString&     key,
                                                          const QStringList& params )
{
    qRegisterMetaType<KeyboardLayoutType::Type>();

    if ( key.compare( "openvirtualkeyboard", Qt::CaseInsensitive ) != 0 )
        return nullptr;

    auto inputContext = new OpenVirtualKeyboardInputContext( params );
    QQmlEngine::setObjectOwnership( inputContext, QQmlEngine::CppOwnership );
    gInputContext = inputContext;

    const char* uri = "OpenVirtualKeyboard";

    qmlRegisterSingletonType<OpenVirtualKeyboardInputContext>(
        uri, 1, 0, "InputContext", inputContextProvider );
    qmlRegisterType( QUrl( "qrc:///ovk/qml/Keyboard.qml" ), uri, 1, 0, "Keyboard" );
    qmlRegisterType<Key>( uri, 1, 0, "Key" );
    qmlRegisterType<KeyPressInterceptor>( uri, 1, 0, "KeyPressInterceptor" );
    qmlRegisterType<KeyPreview>( uri, 1, 0, "KeyPreview" );
    qmlRegisterType<KeyAlternativesPreview>( uri, 1, 0, "KeyAlternativesPreview" );
    qmlRegisterType<KeyboardStyle>( uri, 1, 0, "KeyboardStyle" );
    qmlRegisterUncreatableType<KeyboardLayoutModel>(
        uri, 1, 0, "KeyboardLayoutModel", "KeyboardLayoutModel is not creatable type" );
    qmlRegisterUncreatableType<KeyboardLayoutsProvider>(
        uri, 1, 0, "KeyboardLayoutsProvider", "KeyboardLayoutsProvider is not creatable type" );
    qmlRegisterUncreatableMetaObject( KeyboardLayoutType::staticMetaObject,
                                      uri,
                                      1,
                                      0,
                                      "KeyboardLayoutType",
                                      "Error: only enums" );

    return inputContext;
}
