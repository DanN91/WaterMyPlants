/*
    TimerMode: watering mode which controls a water pump, turning it on and off based on set time frequency and duration.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "TimerMode.h"

#include "Constants.h"
#include <EEPROM.h>

TimerMode::TimerMode(WaterPump &waterPump)
    : m_waterPump(waterPump)
{
    // read from persistent storage
    EEPROM.get<uint16_t>(Constants::Addresses::WATERING_DURATION_SECONDS, WATERING_DURATION_SEC);
    EEPROM.get<uint16_t>(Constants::Addresses::WATERING_FREQUENCY_MINUTES, WATERING_FREQUENCY_MIN);

    // Serial.println(WATERING_TIME_MS);
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
    if (!m_waterPump.IsOn() && (currentMs - m_timeToWaterCounterMs) >= (WATERING_FREQUENCY_MIN * Constants::Time::MINUTE_MS))
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