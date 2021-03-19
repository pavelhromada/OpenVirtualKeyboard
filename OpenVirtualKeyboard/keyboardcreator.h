/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#ifndef KEYBOARDCREATOR_H
#define KEYBOARDCREATOR_H

#include <memory>
#include <QObject>
#include <QQmlIncubator>

class QQmlEngine;
class QQuickWindow;
class QQuickItem;
class QQmlComponent;
class QQmlIncubationController;
class QGuiApplication;
class KeyPressInterceptor;

class KeyboardCreator : public QObject, public QQmlIncubator
{
    Q_OBJECT
public:
    KeyboardCreator( const QUrl& keyboardUrl );
    ~KeyboardCreator() override;

    void createKeyboard();

    QObject* keyboardObject() const;
    KeyPressInterceptor* keyPressInterceptor() const;

signals:
    void created();

    // QQmlIncubator interface
protected:
    void statusChanged( Status status ) override;

private:
    void continueKeyboardCreation();
    QGuiApplication* applicationInstance() const;
    void createKeyboardInstance();
    QQmlEngine* usedQmlEngine() const;
    QQuickWindow* usedWindow() const;

    QUrl                                      _keyboardUrl;
    bool                                      _loading = false;
    std::unique_ptr<QQmlComponent>            _keyboardComponent;
    std::unique_ptr<QQmlIncubationController> _incubationController;
    QObject*                                  _keyboard            = nullptr;
    KeyPressInterceptor*                      _keyPressInterceptor = nullptr;
};

#endif // KEYBOARDCREATOR_H
