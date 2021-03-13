#include <QtMath>
#include <QQuickItem>
#include "commonpositioner.h"
#include "keypressinterceptor.h"
#include "keypreview.h"
#include "keyalternativespreview.h"
#include "key.h"

void CommonPositioner::init( QQuickItem* keyboard )
{
    if (!keyboard)
        return;

    _keyboard            = keyboard;
    _keyPressInterceptor = keyboard->findChild<KeyPressInterceptor*>( "keyInterceptor" );
    _keyPreview          = keyboard->findChild<KeyPreview*>( "keyPreview" );
    _keyAlternatives     = keyboard->findChild<KeyAlternativesPreview*>( "keyAlternatives" );

    connect( _keyPressInterceptor,
             &KeyPressInterceptor::keyClicked,
             this,
             &CommonPositioner::onKeyClicked );
    connect( _keyPressInterceptor,
             &KeyPressInterceptor::alternativesRequired,
             this,
             &CommonPositioner::onAlternativesRequired );
    connect( _keyPressInterceptor,
             &KeyPressInterceptor::alternativePositionMoved,
             this,
             &CommonPositioner::onAlternativePositionMoved );
    connect( _keyPressInterceptor,
             &KeyPressInterceptor::keyActivated,
             this,
             &CommonPositioner::onKeyActivated );
    connect( _keyPressInterceptor,
             &KeyPressInterceptor::activeKeyLeaved,
             this,
             &CommonPositioner::onActiveKeyLeaved );
}

QString CommonPositioner::selectedAlternative() const
{
    _keyPreview->setVisible( false );
    _keyAlternatives->setVisible( false );

    const auto index        = _keyAlternatives->alternativeIndex();
    const auto alternatives = _keyAlternatives->alternatives();

    if (index >= 0 && index < alternatives.count())
        return alternatives.at( index );

    return QString();
}

void CommonPositioner::onKeyClicked( Key* /*key*/ )
{
    _keyPreview->setVisible( false );
    _keyAlternatives->setVisible( false );
}

void CommonPositioner::onAlternativesRequired( Key* key, qreal interceptorX )
{
    const auto alternatives = key->alternatives();

    if (!alternatives.isValid())
        return;

    QStringList alternativesModel;

    if (alternatives.canConvert<QString>()) {
        const auto str = alternatives.toString();
        std::copy( str.begin(), str.end(), std::back_inserter( alternativesModel ));
    } else if (alternatives.canConvert<QJSValue>()) {
        const auto array = alternatives.value<QJSValue>();
        const int length = array.property("length").toInt();
        for (int i = 0; i < length; ++i)
            alternativesModel.append( array.property( i ).toString() );
    }

    if (!alternativesModel.isEmpty()) {
        updateKeyPreview( nullptr );
        updateAlternativesPreview( alternativesModel, key );
        onAlternativePositionMoved( interceptorX );
    }
}

void CommonPositioner::onAlternativePositionMoved( qreal interceptorX )
{
    const auto x = _keyPressInterceptor->mapToItem( _keyAlternatives, QPointF( interceptorX, 0 )).x();
    const auto alternativeWidth = _keyAlternatives->width() / _keyAlternatives->alternatives().count();
    int index = qFloor( x / alternativeWidth );
    index = qMax( 0, qMin( _keyAlternatives->alternatives().count() - 1, index ));
    _keyAlternatives->setAlternativeIndex( index );
}

void CommonPositioner::onKeyActivated( Key* key )
{
    updateKeyPreview( key );
}

void CommonPositioner::onActiveKeyLeaved()
{
    updateKeyPreview( nullptr );
}

void CommonPositioner::updateKeyPreview( Key* key )
{
    _keyAlternatives->setVisible( false );

    if (!key || key->type() != Key::KeyDefault) {
        _keyPreview->setVisible( false );
        return;
    }

    const auto topLeft = _keyPressInterceptor->mapFromItem( key, QPointF( 0, 0 ));
    _keyPreview->setKeyWidth( key->width() );
    _keyPreview->setKeyHeight( key->height() );
    _keyPreview->setKeyText( key->text() );
    auto previewDelegate = _keyPreview->delegate();
    _keyPreview->setWidth( previewDelegate->width() );
    _keyPreview->setHeight( previewDelegate->height() );
    _keyPreview->setY( topLeft.y() - ( previewDelegate->height() - key->height() ));
    qreal x = (topLeft.x() + (key->width() / 2) - (_keyPreview->width() / 2));
    if (x < 0)
        x = _keyboard->mapToItem( _keyPressInterceptor, QPointF( 0, 0 )).x();
    _keyPreview->setX( x );
    _keyPreview->setVisible( true );
}

void CommonPositioner::updateAlternativesPreview( const QStringList& alternativesModel, Key* key )
{
    const auto topLeft = _keyPressInterceptor->mapFromItem( key, QPointF( 0, 0 ));
    _keyAlternatives->setKeyWidth( key->width() );
    _keyAlternatives->setKeyHeight( key->height() );
    _keyAlternatives->setAlternatives( alternativesModel );
    auto previewDelegate = _keyAlternatives->delegate();
    _keyAlternatives->setWidth( previewDelegate->width() );
    _keyAlternatives->setHeight( previewDelegate->height() );
    _keyAlternatives->setY( topLeft.y() - ( previewDelegate->height() - key->height() ));
    qreal x = (topLeft.x() + (key->width() / 2) - (_keyAlternatives->width() / 2));

    if (_keyAlternatives->width() > _keyboard->width())
        x = _keyboard->mapToItem( _keyPressInterceptor, QPointF( 0, 0 )).x();
    else if (x < 0)
        x = _keyboard->mapToItem( _keyPressInterceptor, QPointF( 0, 0 )).x();
    else if (x + _keyAlternatives->width() > _keyPressInterceptor->width())
        x = _keyboard->mapToItem( _keyPressInterceptor, QPointF( _keyboard->width(), 0 )).x()
            - _keyAlternatives->width();

    _keyAlternatives->setX( x );
    _keyAlternatives->setVisible( true );
}
