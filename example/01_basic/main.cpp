#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLoggingCategory>
#include "../shared/examples_shared.h"

int main( int argc, char* argv[] )
{
//    qputenv( "QT_IM_MODULE", "openvirtualkeyboard" );
//    qputenv( "QT_IM_MODULE", "openvirtualkeyboard:immediateLoading" );
//    qputenv( "QT_IM_MODULE", "openvirtualkeyboard:immediateLoading:ownWindow" );
    qputenv( "QT_IM_MODULE", "openvirtualkeyboard:immediateLoading" ); // animateRollout

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
