#ifndef UTILS_H
#define UTILS_H

#include <QMetaType>
#include <QObject>
#include <QVariant>

namespace ovk
{

QString pluginAbsolutePath();
QString stylesAbsolutePath();
QString layoutsAbsolutePath();

template <typename T>
T propertyValue( QObject* object, const char* name, T defaultValue, bool& valid )
{
    if ( !object ) {
        valid = false;
        return defaultValue;
    }
    auto value = object->property( name );
    valid      = value.isValid()
        && static_cast<QMetaType::Type>( value.type() )
            == static_cast<QMetaType::Type>( qMetaTypeId<T>() );
    return valid ? value.value<T>() : defaultValue;
}

}; // namespace ovk

#endif // UTILS_H
