#include "key.h"

bool Key::active() const
{
    return _active;
}

void Key::onPressed()
{
    setActive( true );
}

void Key::onEntered()
{
    setActive( true );
}

void Key::onExited()
{
    setActive( false );
}

void Key::onReleased( bool isClick )
{
    setActive( false );
    if (isClick)
        emit clicked();
}

void Key::setActive( bool active )
{
    if (_active == active)
        return;

    _active = active;
    emit activeChanged();
}

Key::Type Key::type() const
{
    return _type;
}

QVariant Key::alternatives() const
{
    return _alternatives;
}

QQuickItem* Key::delegate() const
{
    return _delegate;
}

QString Key::text() const
{
    return _text;
}

void Key::setType( Key::Type type )
{
    if (_type == type)
        return;

    _type = type;
    emit typeChanged();
}

void Key::setAlternatives( const QVariant& alternatives )
{
    if (_alternatives == alternatives)
        return;

    _alternatives = alternatives;
    emit alternativesChanged();
}

void Key::setText(const QString &text)
{
    if (_text == text)
        return;

    _text = text;
    emit textChanged();
}

void Key::setDelegate( QQuickItem* delegate )
{
    if (_delegate == delegate)
        return;

    _delegate = delegate;
    if (_delegate)
        _delegate->setParentItem( this );

    emit delegateChanged();
}
