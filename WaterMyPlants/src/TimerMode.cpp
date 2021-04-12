/*
    ...
*/

#include "TimerMode.h"
#include "Constants.h"

#include <EEPROM.h>


TimerMode::TimerMode(WaterPump &waterPump)
    : m_waterPump(waterPump)
    // , WATERING_TIME_MS(EEPROM.read(Constants::WATERING_TIME_SEC_ADDRESS) * 1000) // #DNN:ToDo:Consider caching & observing
    , WATERING_TIME_MS(5 * Constants::SECOND_MS) // #DNN:ToDo:Consider caching & observing
{
    m_timeToWaterCounterMs = millis();
}

void TimerMode::Run()
{
    volatile auto currentMs = millis();
    if (!m_waterPump.IsOn() && (currentMs - m_timeToWaterCounterMs) >= Constants::TIME_TO_WATER_MS)
    {
        // pump ON
        m_waterPump.TurnOn();
        // Serial.println("AM: Pump ON");

        m_startedWateringAtMs = millis();
        // Serial.println(WATERING_TIME_MS);
    }
    else if (m_waterPump.IsOn() && (currentMs - m_startedWateringAtMs) >= WATERING_TIME_MS)
    {
        m_waterPump.TurnOff();
        m_timeToWaterCounterMs = millis();
    }
}