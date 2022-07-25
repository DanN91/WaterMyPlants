/*
    TimerMode: watering mode which controls a water pump, turning it on and off based on set time frequency and duration.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "TimerMode.h"

#include "Constants.h"

#include <SettingsManager.h>

TimerMode::TimerMode(WaterPump &waterPump, IObservable<TimerEvent> &timerManager)
    : IObserver(TimerEvent::Minute, timerManager), m_waterPump(waterPump)
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

        SetEvents(TimerEvent::Second);
        m_elapsedDays = 0; // reset counter
    }
    else if (IsTimeToStopWatering())
    {
        // turn off and start counting for next watering
        m_waterPump.TurnOff();

        SetEvents(TimerEvent::Day);
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
    switch (Events() & event)
    {
        case TimerEvent::Second:
        {
            m_elapsedSeconds++;
            break;
        }

        case TimerEvent::Day:
        {
            m_elapsedDays++;
            break;
        }
    }
}

inline bool TimerMode::IsTimeToStartWatering() const
{
    return !m_waterPump.IsOn() && (m_elapsedDays >= SettingsManager::Read(Settings::Address::TimerModeFrequency));
}

inline bool TimerMode::IsTimeToStopWatering() const
{
    return m_waterPump.IsOn() && (m_elapsedSeconds >= SettingsManager::Read(Settings::Address::TimerModeDuration));
}