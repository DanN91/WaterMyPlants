/*
    ...
*/

#include "ManualMode.h"

#include "PushButtonMasks.h"

namespace
{
    static constexpr uint32_t MAX_ON_TIME_LIMIT_MS = 120000u; // 90 seconds should suffice
} // anonymous

ManualMode::ManualMode(WaterPump& waterPump, IObservable<ButtonState>& button)
    : IObserver<ButtonState>(ButtonState::Released, button)
    , m_waterPump(waterPump)
{
}

void ManualMode::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
    {
        // Serial.println("MM:Released");
        m_waterPump.IsOn() ? m_waterPump.TurnOff() : m_waterPump.TurnOn();

        if (m_waterPump.IsOn())
            m_lastOn = millis();
    }
}

void ManualMode::Run()
{
    // safeguard against too much watering
    if (m_waterPump.IsOn() && (millis() - m_lastOn) > MAX_ON_TIME_LIMIT_MS)
    {
        // Serial.println("MM:Safeguard stop");
        m_waterPump.TurnOff();
    }
}