/*
    ...
*/

#pragma once

#include <WaterPump.h>

#include <IOperationMode.h>

class TimerMode final : public IOperationMode
{
public:
    TimerMode(WaterPump& waterPump);

    // IOperationMode
    void Run() override;

private:
    WaterPump& m_waterPump;
    uint32_t m_startedWateringAtMs = 0;
    uint32_t m_timeToWaterCounterMs = 0;
    const uint32_t WATERING_TIME_MS = 0;
};