/*
    SensorMode: Waters the plants by night autonomously using a light and a soil moisture sensor.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <IOperationMode.h>
#include <ObserverPattern.h>

#include <SoilMoistureSensor.h>
#include <LightSensor.h>
#include <WaterPump.h>

class SettingsManager;

class SensorMode final : public IOperationMode, public IObserver<SoilMoistureEvent>, public IObserver<LightSensorEvent>
{
public:
    SensorMode(SoilMoistureSensor& soilMoistureSensor, LightSensor& lightSensor, WaterPump& waterPump, SettingsManager& settings);
    ~SensorMode();

    // IObserver
    void OnEvent(LightSensorEvent event) override;
    void OnEvent(SoilMoistureEvent event) override;

    // IOperationMode
    void Run() override;
    void Activate() override;
    void Deactivate() override;

private:
    void StartWatering();
    void StopWatering();

    // wrappers
    bool IsSoilDry() const;
    bool IsSoilWet() const;
    bool IsNight() const;
    bool IsTimeToTakeABrake() const;

    void HandleSensorsChanges();

    mutable bool m_isBreakNow = false;
    uint32_t m_startedAtMs = 0;
    uint32_t m_stoppedAtMs = 0;

    SettingsManager& m_settings;
    SoilMoistureSensor& m_soilMoistureSensor;
    LightSensor& m_lightSensor;
    WaterPump& m_waterPump;
};