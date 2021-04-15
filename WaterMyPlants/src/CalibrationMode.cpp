/*
    CalibrationMode: allows the user to set the watering duration and frequency and storing that value persistently for further usage.
    Author: Daniel Nistor
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
        if (const auto duration = m_stopwatch.DurationSec(); duration != EEPROM.get<uint16_t>(Constants::Addresses::WATERING_DURATION_SECONDS, storedDuration))
        {
            EEPROM.put<uint16_t>(Constants::Addresses::WATERING_DURATION_SECONDS, duration);
            Serial.print("CM:Watering time: ");
            Serial.println(duration);

            // #DNN:ToDo:Implement storing also the WATERING FREQUENCY
        }
    }
}

void CalibrationMode::Run()
{
}