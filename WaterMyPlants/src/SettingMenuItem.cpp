/*
    SettingMenuItem: represents data for a menu item.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "SettingMenuItem.h"

SettingMenuItem::SettingMenuItem(Strings::Address stringAddress, Settings::Address settingAddress)
    : IMenuItem()
    , m_settingAddress(settingAddress)
    , m_text(StringsManager().Read(stringAddress))
{
}

Settings::Address SettingMenuItem::Address() const
{
    return m_settingAddress;
}

const char* SettingMenuItem::Text() const
{
    return m_text.c_str();
}

uint32_t SettingMenuItem::Value() const
{
    return static_cast<uint32_t>(SettingsManager::Read(m_settingAddress));
}