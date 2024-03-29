/*
    ...
*/

#include "ManualMode.h"

#include "PushButtonMasks.h"

namespace
{
    static constexpr uint32_t MAX_ON_TIME_LIMIT_MS = 300000u; // 5 minutes
} // anonymous

ManualMode::ManualMode(WaterPump& waterPump, IObservable<ButtonState>& button)
    : IObserver(ButtonState::Released, button)
    , m_waterPump(waterPump)
{
}

ManualMode::~ManualMode()
{
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();
}

void ManualMode::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
    {
        m_waterPump.IsOn() ? m_waterPump.TurnOff() : m_waterPump.TurnOn();

        if (m_waterPump.IsOn())
            m_lastOn = millis();
    }
}

void ManualMode::Run()
{
    // safeguard against too much watering
    if (m_waterPump.IsOn() && (millis() - m_lastOn) > MAX_ON_TIME_LIMIT_MS)
        m_waterPump.TurnOff();
}

void ManualMode::Activate()
{
    Register();
}

void ManualMode::Deactivate()
{
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();

    Unregister();
}