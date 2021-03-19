/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#ifndef ABSTRACTPOSITIONER_H
#define ABSTRACTPOSITIONER_H

#include <QObject>
#include <QString>

class QQuickItem;

class AbstractPositioner : public QObject
{
    Q_OBJECT
public:
    virtual void setKeyboardObject( QObject* keyboardObject ) = 0;
    virtual void enableAnimation( bool enabled ) = 0;
    virtual void updateFocusItem( QQuickItem* focusItem ) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual bool isAnimating() const = 0;
    virtual QString selectedAlternative() const = 0;

signals:
    void animatingChanged();
};

#endif // ABSTRACTPOSITIONER_H
