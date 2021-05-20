/*
    MenuCreator: creates a menu.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "MenuCreator.h"

#include <SettingsManager.h>
#include <StringsManager.h>

#include <MenuItem.h>

Menu MenuCreator::Create(MenuCode menuCode)
{
    Menu menu;

    switch (menuCode)
    {
        case MenuCode::Manual:
        {
            menu.Title(Strings::Address::ManualModeTitle);
            break;
        }

        case MenuCode::Timer:
        {
            menu.Title(Strings::Address::TimerModeTitle);

            menu.AddMenuItem({ Strings::Address::TimerModeDuration, Settings::Address::TimerModeDuration });
            menu.AddMenuItem({ Strings::Address::TimerModeFrequency, Settings::Address::TimerModeFrequency });
            break;
        }

        case MenuCode::Sensor:
        {
            menu.Title(Strings::Address::SensorModeTitle);

            menu.AddMenuItem({ Strings::Address::SensorModeDry, Settings::Address::SensorModeDry });
            menu.AddMenuItem({ Strings::Address::SensorModeWet, Settings::Address::SensorModeWet });
            menu.AddMenuItem({ Strings::Address::SensorModeLightThreshold, Settings::Address::SensorModeLightThreshold });
            break;
        }
    }

    return menu;
}