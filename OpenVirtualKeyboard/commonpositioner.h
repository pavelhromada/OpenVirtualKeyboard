/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#ifndef COMMONPOSITIONER_H
#define COMMONPOSITIONER_H

#include "abstractpositioner.h"

class KeyPressInterceptor;
class KeyPreview;
class KeyAlternativesPreview;
class Key;

class CommonPositioner : public AbstractPositioner
{
public:
    void init( QQuickItem* keyboard );
    QString selectedAlternative() const override;

protected:
    void onKeyClicked( Key* key );
    void onAlternativesRequired( Key* key , qreal interceptorX );
    void onAlternativePositionMoved( qreal interceptorX );
    void onKeyActivated( Key* key );
    void onActiveKeyLeaved();
    void updateKeyPreview( Key* key );
    void updateAlternativesPreview( const QStringList& alternativesModel, Key* key );

    QQuickItem*             _keyboard            = nullptr;
    KeyPressInterceptor*    _keyPressInterceptor = nullptr;
    KeyPreview*             _keyPreview          = nullptr;
    KeyAlternativesPreview* _keyAlternatives     = nullptr;
};

#endif // COMMONPOSITIONER_H
