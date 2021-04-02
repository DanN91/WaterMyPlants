/*
    MenuItem: represents data for a menu item.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <SettingsManager.h>
#include <StringsManager.h>

class MenuItem final
{
public:
    MenuItem(Strings::Address stringAddress, Settings::Address settingAddress);

    MenuItem() = default;
    ~MenuItem() = default;

    // copyable and movable
    MenuItem(const MenuItem&) = default;
    MenuItem& operator=(const MenuItem&) = default;

    MenuItem(MenuItem&&) = default;
    MenuItem& operator=(MenuItem&&) = default;

    Strings::Address Text() const;
    Settings::Address Value() const;

private:
    Strings::Address m_stringAddress = Strings::Address::Invalid;
    Settings::Address m_settingAddress = Settings::Address::Invalid;
};
