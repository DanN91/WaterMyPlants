/*
    SettingsManager: wrapper over EEPROM which aids in writing and reading data from EEPROM.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "SettingsManager.h"

#include <EEPROM.h>

using namespace Settings;

void SettingsManager::WriteDefaultSettings()
{
    Write(Address::TimerModeDuration, 60); // 60 seconds
    Write(Address::TimerModeFrequency, 1); // every 1 day
    Write(Address::LastOperationMode, 0); // Manual mode
    Write(Address::SensorModeDry, 20); // 20 %
    Write(Address::SensorModeWet, 70); // 70 %
}

uint32_t SettingsManager::Read(Settings::Address address) const
{
    switch (address)
    {
        case Address::TimerModeDuration:
            return ReadShort(address);

        case Address::TimerModeFrequency: 
        case Address::SensorModeDry:
        case Address::SensorModeWet:
        case Address::LastOperationMode:
            return ReadByte(address);

        default:
            return INVALID_VALUE;
    }
}

bool SettingsManager::Write(Settings::Address address, uint32_t value)
{
    // address check
    const auto addressValue = static_cast<uint16_t>(address);
    if (addressValue < SETTINGS_BEGIN || addressValue >= SETTINGS_END)
        return false;

    // value check
    if (const auto limits = GetLimits(address); (address != Address::LastOperationMode) && !limits.IsInRange(value)) // exception, because it's not set by user directly
        return false;

    switch (address)
    {
        case Address::TimerModeDuration:
        {
            WriteShort(address, value);
            break;
        }

        case Address::TimerModeFrequency: 
        case Address::SensorModeDry:
        case Address::SensorModeWet:
        case Address::LastOperationMode:
        {
            WriteByte(address, value);
            break;
        }

        default:
            return false;
    }

    return true;
}

Settings::Limits SettingsManager::GetLimits(Settings::Address address) const
{
    switch (address)
    {
        case Address::TimerModeDuration:
            return { 1, 300 }; // 5 min

        case Address::TimerModeFrequency:
            return { 1, 7 }; // 7 days

        case Address::SensorModeDry:
            return { 5, 50 }; // #DNN:Test real-world

        case Address::SensorModeWet:
            return { 30, 90 };
    }

    return { 0, 0 };
}

void SettingsManager::WriteByte(Settings::Address address, uint8_t value)
{
    EEPROM[static_cast<uint8_t>(address)] = value;
}

uint8_t SettingsManager::ReadByte(Settings::Address address) const
{
    return EEPROM[static_cast<uint16_t>(address)];
}

void SettingsManager::WriteShort(Settings::Address address, uint16_t value)
{
    EEPROM.put<uint16_t>(static_cast<uint16_t>(address), value);
}

uint16_t SettingsManager::ReadShort(Settings::Address address) const
{
    uint16_t value = 0;
    EEPROM.get<uint16_t>(static_cast<uint16_t>(address), value);

    return value;
}