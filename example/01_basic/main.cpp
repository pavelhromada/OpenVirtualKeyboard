#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLoggingCategory>
#include "../shared/examples_shared.h"

int main( int argc, char* argv[] )
{
    // You may try to add any of the following optional parameters:
    // :animateRollout:immediateLoading:ownWindow:noContentScrolling
    qputenv( "QT_IM_MODULE", "openvirtualkeyboard" );

    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );
    QLoggingCategory::setFilterRules( "*.debug=false\nopenvirtualkeyboard.debug=true\nqml.debug=true" );

    QGuiApplication app( argc, argv );

    CHECK_PLUGIN_IS_PREPARED

    QQmlApplicationEngine engine;
    const QUrl            url( QStringLiteral( "qrc:/main.qml" ) );

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url]( QObject* obj, const QUrl& objUrl ) {
            if ( !obj && url == objUrl )
                QCoreApplication::exit( -1 );
        },
        Qt::QueuedConnection );

    engine.load( url );

    return app.exec();
}
