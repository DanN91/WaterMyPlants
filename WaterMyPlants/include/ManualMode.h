/*
    ...
*/

#pragma once

#include <WaterPump.h>

#include <IObserver.h>
#include <IOperationMode.h>

class ManualMode final : public IObserver, public IOperationMode
{
public:
    ManualMode(WaterPump& waterPump);

    // IObserver
    void OnEvent(uint16_t event) override;

    // IOperationMode
    void Run() override;

private:
    static constexpr uint32_t MAX_ON_TIME_LIMIT_MS = 90000u; // 90 seconds should suffice

    WaterPump& m_waterPump;
    uint32_t m_lastOn = 0;
};