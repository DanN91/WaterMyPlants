/*
    Author: Daniel Nistor
    Purpose: Simple interface over one-pin water pump hardware.
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

    // non-movable & non-copyable
    WaterPump(const WaterPump&) = delete;
    WaterPump& operator=(const WaterPump&) = delete;
    WaterPump(WaterPump&&) = delete;
    WaterPump& operator=(WaterPump&&) = delete;

private:
    const uint8_t m_pin;
};