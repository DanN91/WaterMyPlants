/*
    TimerMode: watering mode which controls a water pump, turning it on and off based on set time frequency and duration.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <WaterPump.h>
#include <IOperationMode.h>
#include <ObserverPattern.h>
#include <TimerManager.h>

class SettingsManager;

class TimerMode final : public IOperationMode, public IObserver<TimerEvent>
{
public:
    TimerMode(WaterPump& waterPump, IObservable<TimerEvent>& timerManager);
    ~TimerMode();

    // IOperationMode
    void Run() override;
    void Activate() override;
    void Deactivate() override;

    // IObserver<TimerEvent>
    void OnEvent(TimerEvent event) override;

private:
    // wrappers
    bool IsTimeToStartWatering() const;
    bool IsTimeToStopWatering() const;

    WaterPump& m_waterPump;

    uint32_t m_elapsedSeconds = 0;
    uint8_t m_elapsedDays = 0;
};