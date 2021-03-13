#ifndef KEYPRESSINTERCEPTOR_H
#define KEYPRESSINTERCEPTOR_H

#include <QQuickItem>
#include <QPointer>

class QMouseEvent;
class Key;

class KeyPressInterceptor : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* forwardTo READ forwardTo WRITE setForwardTo NOTIFY forwardToChanged)
    Q_PROPERTY(int repeatDelay READ repeatDelay WRITE setRepeatDelay NOTIFY repeatDelayChanged)
    Q_PROPERTY(int repeatInterval READ repeatInterval WRITE setRepeatInterval NOTIFY repeatIntervalChanged)
public:
    KeyPressInterceptor();

    QQuickItem* forwardTo() const;
    int repeatDelay() const;
    int repeatInterval() const;

public slots:
    void setForwardTo( QQuickItem* forwardTo );
    void setRepeatDelay( int repeatDelay );
    void setRepeatInterval( int repeatInterval );

signals:
    void forwardToChanged();
    void repeatDelayChanged();
    void repeatIntervalChanged();
    void keyClicked( Key* key );
    void keyRepeatClicked( Key* key );
    void alternativesRequired( Key* key, qreal interceptorX );
    void alternativeSelected();
    void alternativePositionMoved( qreal interceptorX );
    void keyActivated( Key* key );
    void activeKeyLeaved();
    void shiftLocked();

protected:
    void mousePressEvent( QMouseEvent* event ) override;
    void mouseMoveEvent( QMouseEvent* event ) override;
    void mouseReleaseEvent( QMouseEvent* event ) override;
    void touchEvent( QTouchEvent* event ) override;
    void timerEvent( QTimerEvent* event ) override;

private:
    void forwardPress( const QPointF& point );
    void forwardMove( const QPointF& point );
    void forwardRelease( const QPointF& point );
    Key* findKey( const QPointF& point ) const;
    bool isTouchAllowed( const QTouchEvent::TouchPoint& point );
    void startProperTimer();
    void stopTimers();
    void stopTimer( int& timerId );

    QPointer<Key>     _lastActive;
    qreal             _lastX              = 0;
    QQuickItem*       _forwardTo          = nullptr;
    int               _touchPointId       = -1;
    int               _actionDelay        = 300;
    int               _repeatInterval     = 50;
    int               _delayTimer         = 0;
    int               _repeatTimer        = 0;
    int               _alternativesTimer  = 0;
    bool              _alternativesOn     = false;
    int               _pressAndHoldTimer  = 0;
    bool              _ignoreShiftRelease = false;
};

#endif // KEYPRESSINTERCEPTOR_H
