/*
    TimerMode: watering mode which controls a water pump, turning it on and off based on set time frequency and duration.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <WaterPump.h>
#include <IOperationMode.h>
#include <PersistenceManager.h>

class TimerMode final : public IOperationMode
{
public:
    TimerMode(WaterPump& waterPump, PersistenceManager& persistence);
    ~TimerMode();

    // IOperationMode
    void Run() override;

private:
    WaterPump& m_waterPump;

    uint32_t m_startedWateringAtMs = 0;
    uint32_t m_timeToWaterCounterMs = 0;

    const uint16_t WATERING_DURATION_SEC = 0;
    const uint8_t WATERING_FREQUENCY_DAYS = 0;
};