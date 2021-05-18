/*
    TimerMode: watering mode which controls a water pump, turning it on and off based on set time frequency and duration.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "TimerMode.h"

#include "Constants.h"

#include <SettingsManager.h>

TimerMode::TimerMode(WaterPump& waterPump, SettingsManager& settings)
    : m_waterPump(waterPump)
    , m_settings(settings)
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
    volatile auto currentMs = millis();

    if (!m_waterPump.IsOn())
    {
        if (const auto WATERING_FREQUENCY_DAYS = m_settings.Read(Settings::Address::TimerModeFrequency); (currentMs - m_timeToWaterCounterMs) >= (WATERING_FREQUENCY_DAYS * Constants::Time::DAY_MS))
        {
            // turn on and track
            m_waterPump.TurnOn();
            m_startedWateringAtMs = millis();
        }
    }
    else if (m_waterPump.IsOn())
    {
        if (const auto WATERING_DURATION_SEC = m_settings.Read(Settings::Address::TimerModeDuration); (currentMs - m_startedWateringAtMs) >= (WATERING_DURATION_SEC * Constants::Time::SECOND_MS))
        {
            // turn off and start counting for next watering
            m_waterPump.TurnOff();
            m_timeToWaterCounterMs = millis();
        }
    }
}

void TimerMode::Activate()
{
    m_timeToWaterCounterMs = millis();
}

void TimerMode::Deactivate()
{
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();
}