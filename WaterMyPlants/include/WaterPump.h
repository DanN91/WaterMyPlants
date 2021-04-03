/*
    Author: Daniel Nistor
    Purpose: Simple interface over water pump hardware.
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

class WaterPump final
{
public:
    WaterPump(uint8_t pin);

    void Initialize() const;

    void TurnOff() const;
    void TurnOn() const;

    bool IsOn() const;

private:
    const uint8_t m_pin;
};