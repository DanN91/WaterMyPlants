/*
    ...
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
    // Serial.print("Started: ");
    // Serial.println(m_startedAtMs);
}

void Stopwatch::Stop()
{
    m_stoppedAtMs = millis();
    // Serial.print("Stopped: ");
    // Serial.println(m_stoppedAtMs);
}

bool Stopwatch::IsRunning() const
{
    return m_startedAtMs > m_stoppedAtMs;
}

uint32_t Stopwatch::DurationMs()
{
    if (m_stoppedAtMs < m_startedAtMs)
    {
        // Serial.println("Stopwatch:Stopped not called!");
        return 0; // not stopped properly
    }

    const auto duration = m_stoppedAtMs - m_startedAtMs;
    // Serial.print(m_stoppedAtMs);
    // Serial.print(" - ");
    // Serial.print(m_startedAtMs);
    // Serial.print(" = ");
    // Serial.println(duration);

    return duration;
}

uint32_t Stopwatch::DurationSec()
{
    return DurationMs() / 1000;
}