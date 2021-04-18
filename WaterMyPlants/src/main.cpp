#include <Arduino.h>

#include <Array.h>

#include <Hardware.h>
#include <PushButton.h>
#include <NokiaDisplay.h>
#include <MenuCursor.h>
#include <PersistenceManager.h>
#include <SoilMoistureSensor.h>

#include <OperationModeHandler.h>
#include <RangeValuesGenerator.h>

#include <Menu.h>

PersistenceManager persistenceManager;

PushButton modeChangerButton(Hardware::MODE_CHANGER_BUTTON_PIN, 2);
OperationModeHandler operationHandler(modeChangerButton, persistenceManager);

NokiaDisplay& display = NokiaDisplay::getInstance(6, 5, 4, 3, 2);
PushButton menuNavigationButton(Hardware::MENU_NAVIGATION_BUTTON_PIN, 1);
MenuCursor cursor(display, menuNavigationButton, '>', 2);

SoilMoistureSensor soilMoisture(A2);

void setup()
{
    Serial.begin(9600);

    // initialize hardware components
    modeChangerButton.Initialize();
    menuNavigationButton.Initialize();
    operationHandler.Initialize();

    // stringsManager.WriteAllStrings();
    //persistenceManager.WriteDefaultSettings();
    display.Initialize();

    // display.Write(0, persistenceManager.Get(Strings::Address::ManualModeTitle), NokiaDisplay::Aligned::Center);
    display.SetCursor(1, 0);
    display.Write(persistenceManager.Get(Strings::Address::TitleSeparator));

    Menu timerMenu;
    timerMenu.Title(Strings::Address::TimerModeTitle);
    timerMenu.AddMenuItem({ Strings::Address::TimerModeDuration, Settings::Address::TimerModeDuration });
    timerMenu.AddMenuItem({ Strings::Address::TimerModeFrequency, Settings::Address::TimerModeFrequency });

    display.Write(0, persistenceManager.Get(timerMenu.Title()), NokiaDisplay::Aligned::Center);

    for (auto i = 0; i < timerMenu.ItemsCount(); ++i)
    {
        display.Write(i + 2, persistenceManager.Get(timerMenu.GetMenuItem(i)->Text()), NokiaDisplay::Aligned::Left);
        display.Write(i + 2, persistenceManager.Get(timerMenu.GetMenuItem(i)->Value()), NokiaDisplay::Aligned::Right);
    }
}

void loop()
{
    modeChangerButton.HandleEvents();
    menuNavigationButton.HandleEvents();
    operationHandler.Run();
    cursor.Refresh();
    
    // Serial.print(soilMoisture.Value());
    // Serial.println(" %");
    // delay(500);
}