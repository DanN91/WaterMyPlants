/*
    IMenu: Interface for accessing menu items.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <IMenuItem.h>
#include <StringsManager.h>

class IMenu
{
public:
    IMenu(Strings::Address titleAddress) : m_titleAddress(titleAddress) {}
    virtual ~IMenu() = default;

    Strings::Address Title() const { return m_titleAddress; }

    virtual const IMenuItem* GetMenuItem(uint8_t index) const = 0;
    virtual uint8_t ItemsCount() const = 0;
    virtual void HandleItem(uint8_t itemIndex) = 0;

    // non-copyable & non-movable
    IMenu(const IMenu&) = delete;
    IMenu& operator=(const IMenu&) = delete;
    IMenu(IMenu&&) = delete;
    IMenu& operator=(IMenu&&) = delete;

private:
    Strings::Address m_titleAddress = Strings::Address::Invalid;
};
