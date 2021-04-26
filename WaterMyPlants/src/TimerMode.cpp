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
    , WATERING_DURATION_SEC(settings.Read(Settings::Address::TimerModeDuration))
    , WATERING_FREQUENCY_DAYS(settings.Read(Settings::Address::TimerModeFrequency))
{
    m_timeToWaterCounterMs = millis();
}

TimerMode::~TimerMode()
{
    if (m_waterPump.IsOn())
        m_waterPump.TurnOff();
}

void TimerMode::Run()
{
    volatile auto currentMs = millis();
    if (!m_waterPump.IsOn() && (currentMs - m_timeToWaterCounterMs) >= (WATERING_FREQUENCY_DAYS * Constants::Time::DAY_MS))
    {
        // pump ON
        m_waterPump.TurnOn();
        m_startedWateringAtMs = millis();
    }
    else if (m_waterPump.IsOn() && (currentMs - m_startedWateringAtMs) >= (WATERING_DURATION_SEC * Constants::Time::SECOND_MS))
    {
        m_waterPump.TurnOff();
        m_timeToWaterCounterMs = millis();
    }
}