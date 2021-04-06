/*
    ...
*/

#include "ManualMode.h"

#include "PushButtonMasks.h"

ManualMode::ManualMode(WaterPump& waterPump)
    : IObserver(static_cast<uint16_t>(ButtonState::Clicked), 1)
    , m_waterPump(waterPump)
{
}

void ManualMode::OnEvent(uint16_t event)
{
    m_waterPump.IsOn() ? m_waterPump.TurnOff() : m_waterPump.TurnOn();

    if (m_waterPump.IsOn())
        m_lastOn = millis();
}

void ManualMode::Run()
{
    // safeguard against too much watering
    if (m_waterPump.IsOn() && (millis() - m_lastOn) > MAX_ON_TIME_LIMIT_MS)
        m_waterPump.TurnOff();
}