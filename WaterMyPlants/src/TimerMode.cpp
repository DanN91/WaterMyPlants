/*
    TimerMode: watering mode which controls a water pump, turning it on and off based on set time frequency and duration.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "TimerMode.h"

#include "Constants.h"

#include <SettingsManager.h>

TimerMode::TimerMode(WaterPump& waterPump)
    : m_waterPump(waterPump)
{
}

TimerMode::~TimerMode()
{
    // safety
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();
}

void TimerMode::Run()
{
    if (IsTimeToStartWatering())
    {
        // turn on and start tracking watering time
        m_waterPump.TurnOn();
        m_startedWateringAtMs = millis();
    }
    else if (IsTimeToStopWatering())
    {
        // turn off and start counting for next watering
        m_waterPump.TurnOff();
        m_lastWateringAtMs = millis();
    }
}

void TimerMode::Activate()
{
    m_lastWateringAtMs = millis();
}

void TimerMode::Deactivate()
{
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();
}

inline bool TimerMode::IsTimeToStartWatering() const
{
    const auto WAIT_TO_WATER_DURATION_MS = SettingsManager::Read(Settings::Address::TimerModeFrequency) * Constants::Time::DAY_MS;
    return !m_waterPump.IsOn() && ((millis() - m_lastWateringAtMs) >= WAIT_TO_WATER_DURATION_MS);
}

inline bool TimerMode::IsTimeToStopWatering() const
{
    const auto WATERING_DURATION_MS = SettingsManager::Read(Settings::Address::TimerModeDuration) * Constants::Time::SECOND_MS;
    return m_waterPump.IsOn() && ((millis() - m_startedWateringAtMs) >= WATERING_DURATION_MS);
}