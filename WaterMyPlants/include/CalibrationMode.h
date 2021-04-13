/*
    Author: Daniel Nistor
    Purpose: Decorator over ManualMode responsible with allowing the user to set the watering time via start-stop and storing that value persistently for further usage.
    MIT License, 2021
*/

#pragma once

#include <IOperationMode.h>

#include <PushButtonMasks.h>
#include <ManualMode.h>
#include <Stopwatch.h>

class CalibrationMode final : public IObserver<ButtonState>, public IOperationMode
{
public:
    CalibrationMode(WaterPump& waterPump, IObservable<ButtonState>& button);
    ~CalibrationMode() = default;

    // IObserver
    void OnEvent(ButtonState event) override;

    // IOperationMode
    void Run() override;

private:
    ManualMode m_manualMode;
    Stopwatch m_stopwatch;
};