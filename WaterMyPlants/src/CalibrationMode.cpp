/*
    CalibrationMode: allows the user to set the watering duration and frequency and storing that value persistently for further usage.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "CalibrationMode.h"

#include "Constants.h"

CalibrationMode::CalibrationMode(WaterPump& waterPump, IObservable<ButtonState>& button, SettingsManager& settings)
    : IObserver<ButtonState>(ButtonState::Held, button)
    , m_manualMode(waterPump, button)
    , m_stopwatch(button)
    , m_settings(settings)
{
}

void CalibrationMode::OnEvent(ButtonState event)
{
    if (event == ButtonState::Held)
    {
        // write watering time to persistent storage
        if (const auto duration = m_stopwatch.DurationSec(); duration != m_settings.Read(Settings::Address::TimerModeDuration))
        {
            m_settings.Write(Settings::Address::TimerModeDuration, duration);
            // #DNN:ToDo:Implement storing also the WATERING FREQUENCY
        }
    }
}

void CalibrationMode::Run()
{
}