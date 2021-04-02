#include <Arduino.h>

#include <Hardware.h>
#include <PushButton.h>
#include <NokiaDisplay.h>
#include <MenuCursor.h>
#include <MenuCreator.h>
#include <MenuController.h>
#include <SettingsManager.h>
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
PushButton executionButton(Hardware::EXECUTION_BUTTON_PIN);
OperationModeHandler operationHandler(modeChangerButton);

NokiaDisplay display(Hardware::NOKIA_RESET_PIN,
    Hardware::NOKIA_CHIP_ENABLE_PIN,
    Hardware::NOKIA_DATA_SELECT_PIN,
    Hardware::NOKIA_DATA_IN_PIN,
    Hardware::NOKIA_CLOCK_PIN);
PushButton menuNavigationButton(Hardware::MENU_NAVIGATION_BUTTON_PIN);
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
    // Serial.begin(9600);

    // Operation Mode Handler
    operationHandler.Add(manualMode);
    operationHandler.Add(timerMode);
    operationHandler.Add(sensorMode);

    operationHandler.Initialize();

    // initialize hardware components
    modeChangerButton.Initialize();
    menuNavigationButton.Initialize();
    executionButton.Initialize();
    waterPump.Initialize();

    // call once, then comment and recompile + upload
    // StringsManager stringsManager(Language::English);
    // stringsManager.WriteAllStrings();
    // SettingsManager::WriteDefaultSettings();

    display.Initialize();
    menuController.Initialize();
}

uint32_t previous = millis();

// CALIBRATION ONLY
uint16_t minMoisture = 1000;
uint16_t maxMoisture = 0;

uint16_t minLight = 1000;
uint16_t maxLight = 0;

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

    // on Manual menu show this data for calibration purposes
    if (menuController.IsEmptyMenu() && (millis() - previous) >= 1500) // once every second
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

        display.SetCursor(4, 0);
        display.ClearLine();

        String currentLight("L: ");
        currentLight.concat(lightValue);
        currentLight.concat("/");
        currentLight.concat(lightSensor.Value());
        currentLight.concat(" %");

        display.Write(currentLight);

        display.SetCursor(5, 0);
        display.ClearLine();

        String currentMoisture("M: ");
        currentMoisture.concat(moistureValue);
        currentMoisture.concat("/");
        currentMoisture.concat(soilMoistureSensor.Value());
        currentMoisture.concat(" %");

        display.Write(currentMoisture);

        // Update and show Min and Max
        if (moistureValue < minMoisture)
            minMoisture = moistureValue;

        if (moistureValue > maxMoisture)
            maxMoisture = moistureValue;

        if (lightValue < minLight)
            minLight = lightValue;

        if (lightValue > maxLight)
            maxLight = lightValue;

        String lightStats("L: ");
        lightStats.concat(minLight);
        lightStats.concat("/");
        lightStats.concat(maxLight);

        display.SetCursor(2, 0);
        display.ClearLine();
        display.Write(lightStats);

        String moistureStats("M: ");
        moistureStats.concat(minMoisture);
        moistureStats.concat("/");
        moistureStats.concat(maxMoisture);

        display.SetCursor(3, 0);
        display.ClearLine();
        display.Write(moistureStats);

        previous = millis();
    }
}