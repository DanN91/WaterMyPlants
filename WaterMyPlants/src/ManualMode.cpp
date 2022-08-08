/*
    ...
*/

#include "ManualMode.h"


ManualMode::ManualMode(WaterPump& waterPump, IObservable<ButtonState>& button, IObservable<TimerEvent>& timer)
    : IObserver<ButtonState>(ButtonState::Released, button)
    , IObserver<TimerEvent>(TimerEvent::Minute, timer)
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

        if (!m_waterPump.IsOn())
            m_safetyCounter = 0;
    }
}

void ManualMode::OnEvent(TimerEvent event)
{
    if (m_waterPump.IsOn() && !!(event & TimerEvent::Minute))
    {
        m_safetyCounter++;
        if (m_safetyCounter >= 5) // safeguard against too much watering: 5 minutes max.
        {
            m_waterPump.TurnOff();
            m_safetyCounter = 0;
        }
    }
}

void ManualMode::Run()
{
}

void ManualMode::Activate()
{
    IObserver<ButtonState>::Register();
    IObserver<TimerEvent>::Register();
}

void ManualMode::Deactivate()
{
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();

    IObserver<TimerEvent>::Unregister();
    IObserver<ButtonState>::Unregister();
}