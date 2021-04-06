#pragma once

#include <Arduino.h>

enum class ButtonState : uint16_t
{
    Clicked = 1,
    DoubleClicked = 2,
};