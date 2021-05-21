/*
    MenuCreator: creates a menu.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

#include <IMenu.h>
#include <UniquePtr.h>

enum class MenuCode
{
    Manual,
    Timer,
    Sensor,
    Monitor,
    None // must be last
};

class MenuCreator final
{
public:
    static UniquePtr<IMenu> Create(MenuCode menuCode);
};