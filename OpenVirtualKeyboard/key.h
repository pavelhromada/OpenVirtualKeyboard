#ifndef KEY_H
#define KEY_H

#include <QQuickItem>
#include <QVariant>

class Key : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QVariant alternatives READ alternatives WRITE setAlternatives NOTIFY alternativesChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    enum Type {
        KeyDefault,
        Space,
        Backspace,
        Shift,
        Enter,
        Symbol,
        NextPage,
        Hide,
        Language
    };
    Q_ENUM(Type)

    bool active() const;

    void onPressed();
    void onEntered();
    void onExited();
    void onReleased( bool isClick );

public:
    void setActive( bool active );
    Type type() const;
    QVariant alternatives() const;
    QString text() const;
    QQuickItem* delegate() const;

public slots:
    void setType( Type type );
    void setAlternatives( const QVariant& alternatives );
    void setText( const QString& text );
    void setDelegate( QQuickItem* delegate );

signals:
    void activeChanged();
    void typeChanged();
    void alternativesChanged();
    void textChanged();
    void delegateChanged();
    void clicked();

private:
    bool        _active   = false;
    Type        _type     = KeyDefault;
    QVariant    _alternatives;
    QString     _text;
    QQuickItem* _delegate = nullptr;
};

#endif // KEY_H
