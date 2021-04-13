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
    // safeguard against a too big watering time to INVALID_WATERING_TIME
    if (EEPROM.read(Constants::WATERING_TIME_SEC_ADDRESS) > Constants::MAX_WATERING_TIME_SEC)
        EEPROM.write(Constants::WATERING_TIME_SEC_ADDRESS, Constants::MAX_WATERING_TIME_SEC); // truncate to max
}

void CalibrationMode::OnEvent(ButtonState event)
{
    if (event == ButtonState::Held)
    {
        // write watering time to persistent storage
        if (const auto duration = m_stopwatch.DurationSec(); duration != EEPROM.read(Constants::WATERING_TIME_SEC_ADDRESS))
        {
            EEPROM.write(Constants::WATERING_TIME_SEC_ADDRESS, duration);
            Serial.print("CM:Watering time: ");
            Serial.println(duration);
        }
    }
}

void CalibrationMode::Run()
{
    m_manualMode.Run();
}