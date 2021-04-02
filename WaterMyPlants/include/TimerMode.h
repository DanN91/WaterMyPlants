/*
    TimerMode: watering mode which controls a water pump, turning it on and off based on set time frequency and duration.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <WaterPump.h>
#include <IOperationMode.h>

class SettingsManager;

class TimerMode final : public IOperationMode
{
public:
    TimerMode(WaterPump& waterPump);
    ~TimerMode();

    // IOperationMode
    void Run() override;
    void Activate() override;
    void Deactivate() override;

private:
    WaterPump& m_waterPump;

    uint32_t m_startedWateringAtMs = 0;
    uint32_t m_timeToWaterCounterMs = 0;
};