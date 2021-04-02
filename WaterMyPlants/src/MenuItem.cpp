/*
    MenuItem: represents data for a menu item.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "MenuItem.h"

MenuItem::MenuItem(Strings::Address stringAddress, Settings::Address settingAddress)
    : m_stringAddress(stringAddress)
    , m_settingAddress(settingAddress)
{
}

Strings::Address MenuItem::Text() const
{
    return m_stringAddress;
}

Settings::Address MenuItem::Value() const
{
    return m_settingAddress;
}