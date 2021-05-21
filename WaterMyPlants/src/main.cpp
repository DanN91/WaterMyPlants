#include <Arduino.h>

#include <Hardware.h>
#include <PushButton.h>
#include <NokiaDisplay.h>
#include <MenuCursor.h>
#include <MenuCreator.h>
#include <MenuController.h>
#include <StringsManager.h>

#include <SoilMoistureSensor.h>
#include <LightSensor.h>

#include <OperationModeHandler.h>
#include <RangeValuesGenerator.h>
#include <ChangeSetting.h>

#include <ManualMode.h>
#include <TimerMode.h>
#include <SensorMode.h>

#include <Menu.h>

PushButton modeChangerButton(Hardware::MODE_CHANGER_BUTTON_PIN);
OperationModeHandler operationHandler(modeChangerButton);

NokiaDisplay display(6, 5, 4, 3, 2);
PushButton menuNavigationButton(Hardware::MENU_NAVIGATION_BUTTON_PIN);
PushButton executionButton(Hardware::EXECUTION_BUTTON_PIN);
MenuController menuController(display, modeChangerButton, menuNavigationButton, executionButton, operationHandler);

// Operation Modes
WaterPump waterPump(Hardware::WATER_PUMP_PIN);
ManualMode manualMode(waterPump, executionButton);

TimerMode timerMode(waterPump);

SoilMoistureSensor soilMoistureSensor(Hardware::SOIL_MOISTURE_SENSOR_PIN, SoilMoistureSensor::Sensitivity::Medium);
LightSensor lightSensor(Hardware::LIGHT_SENSOR_PIN, LightSensor::Sensitivity::High);
SensorMode sensorMode(soilMoistureSensor, lightSensor, waterPump);

void setup()
{
    Serial.begin(9600);

    // Operation Mode Handler
    operationHandler.Add(manualMode);
    operationHandler.Add(timerMode);
    operationHandler.Add(sensorMode);
    // operationHandler.Add(monitorMode);

    operationHandler.Initialize();

    // initialize hardware components
    modeChangerButton.Initialize();
    menuNavigationButton.Initialize();
    executionButton.Initialize();
    waterPump.Initialize();

    // call once, then comment and recompile + upload
    //StringsManager stringsManager;
    //stringsManager.WriteAllStrings();
    // settingsManager.WriteDefaultSettings();

    display.Initialize();
    menuController.Initialize();
}

uint32_t previous = millis();

void loop()
{
    // buttons
    modeChangerButton.HandleEvents();
    menuNavigationButton.HandleEvents();
    executionButton.HandleEvents();
    lightSensor.HandleEvents();
    soilMoistureSensor.HandleEvents();

    operationHandler.Run();
    menuController.Handle();

    if ((millis() - previous) >= 1500) // once every second
    {
        const auto PrintSensorValues = [](const char* name, uint16_t rawValue, uint8_t percentValue){
            Serial.print(name);
            Serial.print(rawValue);
            Serial.print(" ( ");
            Serial.print(percentValue);
            Serial.println(" % )");
        };

        const auto lightValue = lightSensor.RawValue();
        // const auto lightPercent = lightSensor.Value();
        // PrintSensorValues("Light: ", lightValue, lightPercent);

        const auto moistureValue = soilMoistureSensor.RawValue();
        // const auto moisturePercent = soilMoistureSensor.Value();
        // PrintSensorValues("Moisture: ", moistureValue, moisturePercent);

        display.SetCursor(5, 0);
        display.ClearLine();
        display.Write(5, moistureValue, NokiaDisplay::Aligned::Left);
        display.Write(5, lightValue, NokiaDisplay::Aligned::Right);

        previous = millis();
    }
}