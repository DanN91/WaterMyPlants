/*
    SensorMode: Waters the plants by night autonomously using a light and a soil moisture sensor.
    Author: Daniel Nistor
    MIT License, 2021
*/
#include "SensorMode.h"

#include <SettingsManager.h>
#include <Constants.h>

namespace
{
    constexpr uint8_t WATERING_DURATION_SEC = 10;
    constexpr uint8_t WAITING_BREAK_MIN = 1;
} // anonymous

SensorMode::SensorMode(SoilMoistureSensor& soilMoistureSensor, LightSensor& lightSensor, WaterPump& waterPump)
    : IObserver<SoilMoistureEvent>(SoilMoistureEvent::MoistureChanged, soilMoistureSensor)
    , IObserver<LightSensorEvent>(LightSensorEvent::IntensityChanged, lightSensor)
    , m_soilMoistureSensor(soilMoistureSensor)
    , m_lightSensor(lightSensor)
    , m_waterPump(waterPump)
{
}

SensorMode::~SensorMode()
{
    StopWatering();
}

void SensorMode::OnEvent(LightSensorEvent event)
{
    // const auto lightPercent = m_lightSensor.Value();

    // Serial.print("Light: ");
    // Serial.println(lightPercent);

    HandleSensorsChanges();
}

void SensorMode::OnEvent(SoilMoistureEvent event)
{
    // const auto moisturePercent = m_soilMoistureSensor.Value();

    // Serial.print("Moisture: ");
    // Serial.println(moisturePercent);

    HandleSensorsChanges();
}

void SensorMode::Run()
{
    if (IsNight() && IsSoilDry())
    {
        if (IsTimeToTakeABrake()) // give some time for water to be absorbed
        {
            StopWatering();
            m_isBreakNow = true;
        }
        else if (!m_isBreakNow)
        {
            StartWatering();
        }
    }
}

void SensorMode::Activate()
{
    IObserver<SoilMoistureEvent>::Register();
    IObserver<LightSensorEvent>::Register();
}

void SensorMode::Deactivate()
{
    StopWatering();
    m_isBreakNow = false; // cancel break

    IObserver<SoilMoistureEvent>::Unregister();
    IObserver<LightSensorEvent>::Unregister();
}

void SensorMode::StartWatering()
{
    if (!m_isBreakNow && !m_waterPump.IsOn())
    {
        m_waterPump.TurnOn();
        m_startedAtMs = millis();
    }
}

void SensorMode::StopWatering()
{
    if (m_waterPump.IsOn())
    {
        m_waterPump.TurnOff();
        m_stoppedAtMs = millis();
    }
}

inline bool SensorMode::IsSoilDry() const
{
    // if watering has started, we need to water until the Wet threshold is reached
    return m_waterPump.IsOn() ? !IsSoilWet() : (m_soilMoistureSensor.Value() <= SettingsManager::Read(Settings::Address::SensorModeDry));
}

inline bool SensorMode::IsSoilWet() const
{
    return m_soilMoistureSensor.Value() >= SettingsManager::Read(Settings::Address::SensorModeWet);
}

inline bool SensorMode::IsNight() const
{
    return m_lightSensor.Value() <= SettingsManager::Read(Settings::Address::SensorModeLightThreshold);
}

bool SensorMode::IsTimeToTakeABrake() const
{
    // true: if watering has run for WATERING_DURATION_SEC and the soil is still not WET
    // take a break and let the soil absorb the water
    // false: if WAITING_BREAK_MIN elapsed and the soil is still DRY
    // restart watering for WATERING_DURATION_SEC
    if (m_waterPump.IsOn() && (millis() - m_startedAtMs) >= (WATERING_DURATION_SEC * Constants::Time::SECOND_MS)) // watering cycle
    {
        return IsSoilDry();
    }
    else if (m_isBreakNow && (millis() - m_stoppedAtMs) >= (WAITING_BREAK_MIN * Constants::Time::MINUTE_MS)) // break is over
    {
        m_isBreakNow = false;
        return IsSoilWet();
    }

    return false;
}

void SensorMode::HandleSensorsChanges()
{
    (IsNight() && IsSoilDry()) ? StartWatering() : StopWatering();

    if (m_isBreakNow && IsSoilWet()) // cancel break
        m_isBreakNow = false;
}