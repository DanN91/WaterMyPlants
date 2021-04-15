/*
    Author: Daniel Nistor
    Purpose: Component responsible with allowing the user to set the watering time via start-stop and storing that value persistently for further usage.
    MIT License, 2021
*/

#include "CalibrationMode.h"
#include "Constants.h"

#include <EEPROM.h>

CalibrationMode::CalibrationMode(WaterPump& waterPump, IObservable<ButtonState>& button)
    : IObserver<ButtonState>(ButtonState::Held, button)
    , m_manualMode(waterPump, button)
    , m_stopwatch(button)
{
}

void CalibrationMode::OnEvent(ButtonState event)
{
    if (event == ButtonState::Held)
    {
        // write watering time to persistent storage
        uint16_t storedDuration = 0;
        if (const auto duration = m_stopwatch.DurationSec(); duration != EEPROM.get<uint16_t>(Constants::WATERING_DURATION_SEC_ADDRESS, storedDuration))
        {
            EEPROM.put<uint16_t>(Constants::WATERING_DURATION_SEC_ADDRESS, duration);
            Serial.print("CM:Watering time: ");
            Serial.println(duration);
        }
    }
}

void CalibrationMode::Run()
{
}