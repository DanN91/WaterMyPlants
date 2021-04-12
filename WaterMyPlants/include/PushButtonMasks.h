#pragma once

#include <Arduino.h>

enum class ButtonState : uint8_t
{
    Pressed = 1,
    Released = 2,
    Held = 4
};

inline ButtonState operator |(ButtonState lhs, ButtonState rhs)
{
    return static_cast<ButtonState>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline ButtonState operator &(ButtonState lhs, ButtonState rhs)
{
    return static_cast<ButtonState>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}