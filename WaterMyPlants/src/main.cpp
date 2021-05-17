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

#include <OperationModeHandler.h>
#include <RangeValuesGenerator.h>
#include <ChangeSetting.h>

#include <Menu.h>

SettingsManager settingsManager;

PushButton modeChangerButton(Hardware::MODE_CHANGER_BUTTON_PIN);
PushButton executionButton(Hardware::EXECUTION_BUTTON_PIN);
OperationModeHandler operationHandler(modeChangerButton, executionButton, settingsManager);

NokiaDisplay display(6, 5, 4, 3, 2);
PushButton menuNavigationButton(Hardware::MENU_NAVIGATION_BUTTON_PIN);
MenuController menuController(display, modeChangerButton, menuNavigationButton, executionButton, operationHandler);

SoilMoistureSensor soilMoisture(Hardware::SOIL_MOISTURE_SENSOR_PIN);

void setup()
{
    Serial.begin(9600);

    // initialize hardware components
    modeChangerButton.Initialize();
    executionButton.Initialize();
    menuNavigationButton.Initialize();

    operationHandler.Initialize();

    // call once, then comment and recompile + upload
    // stringsManager.WriteAllStrings();
    // settingsManager.WriteDefaultSettings();

    display.Initialize();
    menuController.Initialize();
}

uint32_t previous = millis();

void loop()
{
    modeChangerButton.HandleEvents();
    menuNavigationButton.HandleEvents();
    operationHandler.Run();
    menuController.Handle();

    if ((millis() - previous) >= 1000) // once every second
    {
        Serial.print(soilMoisture.Value());
        Serial.println(" %");

        display.SetCursor(5, 0);
        display.ClearLine();
        display.Write(5, soilMoisture.Value(), NokiaDisplay::Aligned::Center);

        previous = millis();
    }
}