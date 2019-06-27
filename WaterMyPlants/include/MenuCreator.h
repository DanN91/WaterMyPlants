/*
    MenuCreator: creates a menu.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <Menu.h>

enum class MenuCode
{
    Manual,
    Timer,
    Sensor,
    None // must be last
};

class MenuCreator final
{
public:
    static Menu Create(MenuCode menuCode);
};