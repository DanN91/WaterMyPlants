/*
    MenuCreator: creates a supported menu.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "MenuCreator.h"

#include <SettingsManager.h>
#include <StringsManager.h>

#include <Menu.h>
#include <IMenuItem.h>
#include <SettingMenuItem.h>

UniquePtr<IMenu> MenuCreator::Create(MenuCode menuCode)
{
    switch (menuCode)
    {
        case MenuCode::Manual:
        {
            return UniquePtr<IMenu>(new Menu<SettingMenuItem>(Strings::Address::ManualModeTitle));
        }

        case MenuCode::Timer:
        {
            auto timerMenu = new Menu<SettingMenuItem>(Strings::Address::TimerModeTitle);
            if (!timerMenu)
                return nullptr;

            timerMenu->AddMenuItem({ Strings::Address::TimerModeDuration, Settings::Address::TimerModeDuration });
            timerMenu->AddMenuItem({ Strings::Address::TimerModeFrequency, Settings::Address::TimerModeFrequency });

            return UniquePtr<IMenu>(timerMenu);
        }

        case MenuCode::Sensor:
        {
            auto sensorMenu = new Menu<SettingMenuItem>(Strings::Address::SensorModeTitle);
            if (!sensorMenu)
                return nullptr;

            sensorMenu->AddMenuItem({ Strings::Address::SensorModeDry, Settings::Address::SensorModeDry });
            sensorMenu->AddMenuItem({ Strings::Address::SensorModeWet, Settings::Address::SensorModeWet });
            sensorMenu->AddMenuItem({ Strings::Address::SensorModeLightThreshold, Settings::Address::SensorModeLightThreshold });

            return UniquePtr<IMenu>(sensorMenu);
        }

        case MenuCode::Monitor:
        {
            auto monitorMenu = new Menu<SettingMenuItem>(Strings::Address::MonitorModeTitle);
            if (!monitorMenu)
                return nullptr;

            // menu.AddMenuItem({ Strings::Address::SensorModeDry, Settings::Address::SensorModeDry });
            // menu.AddMenuItem({ Strings::Address::SensorModeWet, Settings::Address::SensorModeWet });
            // menu.AddMenuItem({ Strings::Address::SensorModeLightThreshold, Settings::Address::SensorModeLightThreshold });

            return UniquePtr<IMenu>(monitorMenu);
        }
    }

    return nullptr;
}