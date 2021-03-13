#ifndef INJECTEDKEYBOARDPOSITIONER_H
#define INJECTEDKEYBOARDPOSITIONER_H

#include <memory>
#include <QObject>
#include <QPointer>
#include <QPropertyAnimation>
#include "commonpositioner.h"

class InjectedKeyboardPositioner : public CommonPositioner
{
    Q_OBJECT
public:
    InjectedKeyboardPositioner();
    ~InjectedKeyboardPositioner() override;

    void setKeyboardObject( QObject* keyboardObject ) override;
    void enableAnimation( bool enabled ) override;
    void updateFocusItem( QQuickItem* focusItem ) override;
    void show() override;
    void hide() override;
    bool isAnimating() const override;

private:
    void updateContentItemPosition( bool updateKeyboardPosition );
    void onHeightChanged();
    void onAnimationFinished();

    bool                                _shown  = false;
    qreal                               _offset = 0;
    std::unique_ptr<QPropertyAnimation> _animation;
    QPointer<QQuickItem>                _keyboard;
    QPointer<QQuickItem>                _contentItem;
    QPointer<QQuickItem>                _focusItem;
};

#endif // INJECTEDKEYBOARDPOSITIONER_H
