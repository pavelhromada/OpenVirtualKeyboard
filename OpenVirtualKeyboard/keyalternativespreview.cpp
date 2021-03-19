/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#include <algorithm>
#include "keyalternativespreview.h"

KeyAlternativesPreview::KeyAlternativesPreview()
{
    setVisible( false );
}

qreal KeyAlternativesPreview::keyWidth() const
{
    return _keyWidth;
}

qreal KeyAlternativesPreview::keyHeight() const
{
    return _heyHeight;
}

QStringList KeyAlternativesPreview::alternatives() const
{
    return _alternatives;
}

QQuickItem* KeyAlternativesPreview::delegate() const
{
    return _delegate;
}

bool KeyAlternativesPreview::uppercase() const
{
    return _uppercase;
}

int KeyAlternativesPreview::alternativeIndex() const
{
    return _alternativeIndex;
}

void KeyAlternativesPreview::setKeyWidth( qreal keyWidth )
{
    if (qFuzzyCompare( _keyWidth, keyWidth ))
        return;

    _keyWidth = keyWidth;
    emit keyWidthChanged();
}

void KeyAlternativesPreview::setKeyHeight( qreal heyHeight )
{
    if (qFuzzyCompare( _heyHeight, heyHeight ))
        return;

    _heyHeight = heyHeight;
    emit keyHeightChanged();
}

void KeyAlternativesPreview::setAlternatives( const QStringList& alternatives )
{
    if (_alternatives == alternatives)
        return;

    _alternatives = applyUppercase( alternatives );
    emit alternativesChanged();
}

void KeyAlternativesPreview::setDelegate( QQuickItem* delegate )
{
    if (_delegate == delegate)
        return;

    _delegate = delegate;
    if (_delegate)
        _delegate->setParentItem( this );
    emit delegateChanged();
}

void KeyAlternativesPreview::setUppercase( bool uppercase )
{
    if (_uppercase == uppercase)
        return;

    _uppercase = uppercase;
    emit uppercaseChanged();
    _alternatives = applyUppercase( _alternatives );
    emit alternativesChanged();
}

QStringList KeyAlternativesPreview::applyUppercase( const QStringList& alternatives )
{
    if (!_uppercase)
        return alternatives;

    QStringList transformed;
    std::transform( std::begin( alternatives ),
                    std::end( alternatives ),
                    std::back_inserter( transformed ),
                    []( const QString& c ) -> QString { return c.toUpper(); });
    return transformed;
}

void KeyAlternativesPreview::setAlternativeIndex( int alternativeIndex )
{
    if (_alternativeIndex == alternativeIndex)
        return;

    _alternativeIndex = alternativeIndex;
    emit alternativeIndexChanged();
}
