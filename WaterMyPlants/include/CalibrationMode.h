/*
    CalibrationMode: allows the user to set the watering duration and frequency and storing that value persistently for further usage.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <IOperationMode.h>

#include <PushButtonMasks.h>
#include <ManualMode.h>
#include <Stopwatch.h>
#include <PersistenceManager.h>

class CalibrationMode final : public IObserver<ButtonState>, public IOperationMode
{
public:
    CalibrationMode(WaterPump& waterPump, IObservable<ButtonState>& button, PersistenceManager& persistence);
    ~CalibrationMode() = default;

    // IObserver
    void OnEvent(ButtonState event) override;

    // IOperationMode
    void Run() override;

private:
    ManualMode m_manualMode;
    Stopwatch m_stopwatch;
    PersistenceManager& m_persistence;
};