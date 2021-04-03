/*
    Author: Daniel Nistor
    Purpose: Simple interface over water pump hardware.
    MIT License, 2021
*/

#include "WaterPump.h"

WaterPump::WaterPump(uint8_t pin)
    : m_pin(pin)
{
}

void WaterPump::Initialize() const
{
    pinMode(m_pin, OUTPUT);
    TurnOff(); // OFF by default
}

void WaterPump::TurnOff() const
{
    digitalWrite(m_pin, LOW);
}

void WaterPump::TurnOn() const
{
    digitalWrite(m_pin, HIGH);
}

bool WaterPump::IsOn() const
{
    return digitalRead(m_pin) == HIGH;
}