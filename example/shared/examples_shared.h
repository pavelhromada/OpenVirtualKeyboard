#ifndef EXAMPLES_SHARED_H
#define EXAMPLES_SHARED_H

#include <cstdlib>
#include <QCoreApplication>
#include <QDir>
#include <QLibrary>
#include <QPluginLoader>
#include <QJsonObject>
#include <QJsonArray>

#define CHECK_PLUGIN_IS_PREPARED \
    { \
        const auto sep = QDir::separator(); \
        const auto path = qApp->applicationDirPath() + sep + "platforminputcontexts" + sep; \
        const auto libraries = QDir( path ).entryList( QDir::Files ); \
        bool found = false; \
        for (auto&& lib : libraries) { \
            if (!QLibrary::isLibrary( lib )) continue; \
            QPluginLoader loader{ path + lib }; \
            const auto metaData = loader.metaData(); \
            if (metaData["MetaData"].toObject()["Keys"].toArray().contains("ovk-magic-key")) { \
                found = true; \
                break; \
            } \
        } \
        if (!found) { \
            qWarning( "Build and copy 'openvirtualkeyboard' plugin into ./out/platforminputcontexts" ); \
            std::exit( EXIT_FAILURE ); \
        } \
    }

#endif // EXAMPLES_SHARED_H
