#include "keypreview.h"

KeyPreview::KeyPreview()
{
    setVisible( false );
}

QQuickItem* KeyPreview::delegate() const
{
    return _delegate;
}

qreal KeyPreview::keyWidth() const
{
    return _keyWidth;
}

qreal KeyPreview::keyHeight() const
{
    return _keyHeight;
}

void KeyPreview::setDelegate( QQuickItem* delegate )
{
    if (_delegate == delegate)
        return;

    _delegate = delegate;
    if (_delegate)
        _delegate->setParentItem( this );
    emit delegateChanged();
}

void KeyPreview::setKeyText( const QString& keyText )
{
    if (_keyText == keyText)
        return;

    _keyText = keyText;
    emit keyTextChanged();
}

void KeyPreview::setKeyHeight(qreal keyHeight)
{
    if (qFuzzyCompare( _keyHeight, keyHeight ))
        return;

    _keyHeight = keyHeight;
    emit keyHeightChanged();
}

QString KeyPreview::keyText() const
{
    return _keyText;
}

void KeyPreview::setKeyWidth( qreal keyWidth )
{
    if (qFuzzyCompare( _keyWidth, keyWidth ))
        return;

    _keyWidth = keyWidth;
    emit keyWidthChanged();
}
