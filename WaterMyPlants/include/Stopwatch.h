/*
    ...
*/

#pragma once

#include <Arduino.h>

#include <PushButtonMasks.h>
#include <PushButton.h>

class Stopwatch final : public IObserver<ButtonState>
{
public:
    Stopwatch(IObservable<ButtonState>& button);
    ~Stopwatch() = default;

    // IObserver
    void OnEvent(ButtonState event) override;

    uint32_t DurationMs();
    uint32_t DurationSec();

private:
    void Start();
    void Stop();
    bool IsRunning() const;

    uint32_t m_stoppedAtMs = 0;
    uint32_t m_startedAtMs = 0;
};