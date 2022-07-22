/*
    TimerMode: watering mode which controls a water pump, turning it on and off based on set time frequency and duration.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "TimerMode.h"

#include "Constants.h"

#include <SettingsManager.h>

TimerMode::TimerMode(WaterPump& waterPump, IObservable<TimerEvent>& timerManager)
    : IObserver(TimerEvent::Second, timerManager) // #DNN:TODO:See what's appropriate
    , m_waterPump(waterPump)
{
}

TimerMode::~TimerMode()
{
    // safety
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();

    Unregister();
}

void TimerMode::Run()
{
    // #TODO:Show countdown timer in <hh>:<mm>:<ss>
    if (IsTimeToStartWatering())
    {
        // turn on and start tracking watering time
        m_waterPump.TurnOn();
        m_elapsedSeconds = 0; // reset counter
    }
    else if (IsTimeToStopWatering())
    {
        // turn off and start counting for next watering
        m_waterPump.TurnOff();
        m_elapsedSeconds = 0; // reset counter
    }
}

void TimerMode::Activate()
{
    Register(); // start getting notified about Timer Events
}

void TimerMode::Deactivate()
{
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();

    Unregister();
}

void TimerMode::OnEvent(TimerEvent event)
{
    if ((event & TimerEvent::Second) == TimerEvent::Second)
    {
        m_elapsedSeconds++;
    }
}

inline bool TimerMode::IsTimeToStartWatering() const
{
    const auto WAIT_TO_WATER_DURATION_SEC = (SettingsManager::Read(Settings::Address::TimerModeFrequency) * Constants::Time::DAY_MS) / Constants::Time::SECOND_MS;
    return !m_waterPump.IsOn() && (m_elapsedSeconds >= WAIT_TO_WATER_DURATION_SEC);
}

inline bool TimerMode::IsTimeToStopWatering() const
{
    const auto WATERING_DURATION_SEC = SettingsManager::Read(Settings::Address::TimerModeDuration);
    return m_waterPump.IsOn() && (m_elapsedSeconds >= WATERING_DURATION_SEC);
}