/*
    IMenuItem: Interface representing a menu item.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

class IMenuItem
{
public:
    IMenuItem() = default;
    virtual ~IMenuItem() = default;

    virtual const char* Text() const = 0;
    virtual uint32_t Value() const = 0;

    // copyable and movable
    IMenuItem(const IMenuItem&) = default;
    IMenuItem& operator=(const IMenuItem&) = default;
    IMenuItem(IMenuItem&&) = default;
    IMenuItem& operator=(IMenuItem&&) = default;
};
