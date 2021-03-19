/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#ifndef KEYBOARDLAYOUTTYPE_H
#define KEYBOARDLAYOUTTYPE_H

#include <QObject>

namespace KeyboardLayoutType
{
    Q_NAMESPACE

    enum Type
    {
        Alphabet,
        Symbols,
        Dial    = Qt::ImhDialableCharactersOnly,
        Numbers = Qt::ImhFormattedNumbersOnly,
        Digits  = Qt::ImhDigitsOnly
    };
    Q_ENUM_NS(Type)
}
#endif // KEYBOARDLAYOUTTYPE_H
