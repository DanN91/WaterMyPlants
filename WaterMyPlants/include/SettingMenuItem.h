/*
    SettingMenuItem: represents data for a menu item.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <IMenuItem.h>

#include <SettingsManager.h>
#include <StringsManager.h>

class SettingMenuItem final : public IMenuItem
{
public:
    SettingMenuItem(Strings::Address stringAddress, Settings::Address settingAddress);

    SettingMenuItem() = default;
    ~SettingMenuItem() = default;

    Settings::Address Address() const;

    // IMenuItem
    const char* Text() const override;
    uint32_t Value() const override;

    SettingsMenuItem(const SettingMenuItem& copy)
    {
        m_text = copy.m_text;
        m_settingAddress = copy.m_settingAddress;
    }

    SettingMenuItem& operator=(const SettingMenuItem& copy)
    {
        if (this != &copy)
        {
            m_text = copy.m_text;
            m_settingAddress = copy.m_settingAddress;
        }
    }

private:
    const String m_text;
    Settings::Address m_settingAddress = Settings::Address::Invalid;
};
