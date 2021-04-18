/*
    CalibrationMode: allows the user to set the watering duration and frequency and storing that value persistently for further usage.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "CalibrationMode.h"

#include "Constants.h"

CalibrationMode::CalibrationMode(WaterPump& waterPump, IObservable<ButtonState>& button, PersistenceManager& persistence)
    : IObserver<ButtonState>(ButtonState::Held, button)
    , m_manualMode(waterPump, button)
    , m_stopwatch(button)
    , m_persistence(persistence)
{
}

void CalibrationMode::OnEvent(ButtonState event)
{
    if (event == ButtonState::Held)
    {
        // write watering time to persistent storage
        if (const auto duration = m_stopwatch.DurationSec(); duration != m_persistence.TimerModeDuration())
        {
            m_persistence.TimerModeDuration(duration);
            Serial.print("CM:Watering time: ");
            Serial.println(duration);

            // #DNN:ToDo:Implement storing also the WATERING FREQUENCY
        }
    }
}

void CalibrationMode::Run()
{
}