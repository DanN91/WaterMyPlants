/*
    Stopwatch: track time in milliseconds or seconds by using a pushbutton for starting and stopping the watch.
    Author: Daniel Nistor
    License: MIT
*/

#include "Stopwatch.h"

Stopwatch::Stopwatch(IObservable<ButtonState>& button)
    : IObserver<ButtonState>(ButtonState::Released, button)
{
}

void Stopwatch::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
        IsRunning() ? Stop() : Start();
}

void Stopwatch::Start()
{
    m_startedAtMs = millis();
}

void Stopwatch::Stop()
{
    m_stoppedAtMs = millis();
}

bool Stopwatch::IsRunning() const
{
    return m_startedAtMs > m_stoppedAtMs;
}

uint32_t Stopwatch::DurationMs() const
{
    return (m_stoppedAtMs < m_startedAtMs) ? 0 : (m_stoppedAtMs - m_startedAtMs);
}

uint32_t Stopwatch::DurationSec() const
{
    return DurationMs() / 1000;
}