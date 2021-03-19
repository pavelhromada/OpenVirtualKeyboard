/**
 *  MIT License
 *  Copyright (c) Pavel Hromada
 *  See accompanying LICENSE file
 */

#include <QGuiApplication>
#include <QStyleHints>
#include <QCursor>
#include "keypressinterceptor.h"
#include "key.h"

KeyPressInterceptor::KeyPressInterceptor()
{
    setAcceptedMouseButtons( Qt::LeftButton );
    setAcceptTouchEvents( true );
    setCursor( Qt::ArrowCursor ); // to prevent Beam cursor, when e.g. InputBox is under keyboard
}

QQuickItem* KeyPressInterceptor::forwardTo() const
{
    return _forwardTo;
}

int KeyPressInterceptor::repeatDelay() const
{
    return _actionDelay;
}

int KeyPressInterceptor::repeatInterval() const
{
    return _repeatInterval;
}

void KeyPressInterceptor::setForwardTo( QQuickItem* forwardTo )
{
    if (_forwardTo == forwardTo)
        return;

    _forwardTo = forwardTo;
    emit forwardToChanged();
}

void KeyPressInterceptor::setRepeatDelay( int repeatDelay )
{
    if (_actionDelay == repeatDelay)
        return;

    _actionDelay = repeatDelay;
    emit repeatDelayChanged();
}

void KeyPressInterceptor::setRepeatInterval( int repeatInterval )
{
    if (_repeatInterval == repeatInterval)
        return;

    _repeatInterval = repeatInterval;
    emit repeatIntervalChanged();
}

void KeyPressInterceptor::forwardPress( const QPointF& point )
{
    if (!_forwardTo || _touchPointId != -1)
        return;
    _lastX = point.x();
    auto to = findKey( point );

    if (to) {
        _lastActive = to;
        if (to->isEnabled()) {
            emit keyActivated( to );
            to->onPressed();
            startProperTimer();
        } else {
            emit activeKeyLeaved();
            _lastActive = nullptr;
        }
    }
}

void KeyPressInterceptor::forwardMove( const QPointF& point )
{
    if (!_forwardTo)
        return;

    _lastX = point.x();

    if (_alternativesOn) {
        emit alternativePositionMoved( point.x() );
        return;
    }

    auto to = findKey( point );

    if (!to) {
        stopTimers();
        if (_lastActive) {
            emit activeKeyLeaved();
            _lastActive->onExited();
            _lastActive = nullptr;
        }
        return;
    }

    if (_lastActive != to) {
        stopTimers();
        if (_lastActive)
            _lastActive->onExited();
        if (to->isEnabled()) {
            _lastActive = to;
            emit keyActivated( to );
            to->onEntered();
            startProperTimer();
        } else {
            emit activeKeyLeaved();
            _lastActive = nullptr;
        }
    }
}

void KeyPressInterceptor::forwardRelease( const QPointF& point )
{
    _touchPointId = -1;
    stopTimers();

    if (_alternativesOn) {
        _alternativesOn = false;
        if (_lastActive) {
            _lastActive->onReleased( false );
            emit alternativeSelected();
        }
        return;
    }

    if (!_forwardTo)
        return;

    auto to = findKey( point );

    if (_ignoreShiftRelease && to && to->type() == Key::Shift) {
        _ignoreShiftRelease = false;
        to->onReleased( false );
        return;
    }

    _ignoreShiftRelease = false;

    if (to && to->isEnabled()) {
        to->onReleased( true );
        emit keyClicked( to );
    }
}

Key* KeyPressInterceptor::findKey( const QPointF& point ) const
{
    auto pos = point;
    auto to = _forwardTo->childAt( pos.x(), pos.y() );
    while (to && !qobject_cast<Key*>( to )) {
        pos = _forwardTo->mapToItem( to, pos );
        to = to->childAt( pos.x(), pos.y() );
    }
    return qobject_cast<Key*>( to );
}

bool KeyPressInterceptor::isTouchAllowed( const QTouchEvent::TouchPoint& point )
{
    if (point.id() == _touchPointId) {
        return true;
    } else if (_touchPointId == -1 && point.state() == Qt::TouchPointPressed) {
        _touchPointId = point.id();
        return true;
    }

    return false;
}

void KeyPressInterceptor::startProperTimer()
{
    if (!_lastActive) {
        stopTimers();
        return;
    }

    auto type = _lastActive->type();

    if (type == Key::Shift) {
        _pressAndHoldTimer = startTimer( QGuiApplication::styleHints()->mousePressAndHoldInterval() );
        return;
    }

    if (type == Key::Space || type == Key::Backspace) {
        _delayTimer = startTimer( _actionDelay );
        return;
    }

    if (type == Key::KeyDefault) {
        const auto alternatives = _lastActive->alternatives();
        if (!alternatives.isValid() || alternatives.isNull())
            _delayTimer = startTimer( _actionDelay );
        else
            _alternativesTimer = startTimer( _actionDelay );
    }
}

void KeyPressInterceptor::stopTimers()
{
    stopTimer( _delayTimer );
    stopTimer( _repeatTimer );
    stopTimer( _alternativesTimer );
    stopTimer( _pressAndHoldTimer );
}

void KeyPressInterceptor::stopTimer( int& timerId )
{
    if (timerId > 0) {
        killTimer( timerId );
        timerId = 0;
    }
}

void KeyPressInterceptor::mousePressEvent( QMouseEvent* event )
{
    forwardPress( event->localPos() );
}

void KeyPressInterceptor::mouseMoveEvent( QMouseEvent* event )
{
    forwardMove( event->localPos() );
}

void KeyPressInterceptor::mouseReleaseEvent( QMouseEvent* event )
{
    forwardRelease( event->localPos() );
}

void KeyPressInterceptor::touchEvent( QTouchEvent* event )
{
    switch (event->type()) {
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
            for (auto&& point : event->touchPoints()) {
                if (!isTouchAllowed( point ))
                    continue;
                switch (point.state()) {
                    case Qt::TouchPointPressed:
                        forwardPress( point.pos() );
                        break;
                    case Qt::TouchPointMoved:
                        forwardMove( point.pos() );
                        break;
                    case Qt::TouchPointReleased:
                        forwardRelease( point.pos() );
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}

void KeyPressInterceptor::timerEvent( QTimerEvent* event )
{
    if (event->timerId() == _pressAndHoldTimer) {
        stopTimers();
        _ignoreShiftRelease = true;
        emit shiftLocked();
    } else if (event->timerId() == _delayTimer) {
        stopTimers();
        _repeatTimer = startTimer( _repeatInterval );
    } else if (event->timerId() == _repeatTimer)
        emit keyRepeatClicked( _lastActive );
    else if (event->timerId() == _alternativesTimer) {
        stopTimers();
        _alternativesOn = true;
        if (_lastActive)
            _lastActive->onReleased( false );
        emit alternativesRequired( _lastActive, _lastX );
    }
}
