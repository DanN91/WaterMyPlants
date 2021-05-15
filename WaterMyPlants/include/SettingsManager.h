/*
    SettingsManager: wrapper over EEPROM which aids in writing and reading settings ( numbers ) from EEPROM.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

// Sector in EEPROM
namespace Settings
{
    constexpr uint16_t SETTINGS_BEGIN = 0;
    constexpr uint16_t SETTINGS_END = 199;

    enum class Address : uint16_t
    {
        TimerModeDuration = SETTINGS_BEGIN,
        TimerModeFrequency = TimerModeDuration + sizeof(uint16_t),
        SensorModeDry = TimerModeFrequency + sizeof(uint8_t),
        SensorModeWet = SensorModeDry + sizeof(uint8_t),
        LastOperationMode = SensorModeWet + sizeof(uint8_t),

        // Not found, invalid address
        Invalid = LastOperationMode + sizeof(uint8_t)
    };

    struct Range
    {
    public:
        Range(uint32_t min, uint32_t max, uint16_t step) // make sure the type fits the largest limit size
            : m_min(min),
              m_max(max),
              m_step(step)
        {}

        bool IsInRange(uint32_t value) const { return (value >= m_min) && (value <= m_max); }

        uint32_t Min() const { return m_min; }
        uint32_t Max() const { return m_max; }
        uint16_t Step() const { return m_step; }

    private:
        const uint32_t m_min = 0;
        const uint32_t m_max = 0;
        const uint16_t m_step = 0;
    };

    constexpr const auto INVALID_VALUE = 9999;
}

class SettingsManager final
{
public:
    SettingsManager() = default;
    ~SettingsManager() = default;

    uint32_t Read(Settings::Address address) const;
    bool Write(Settings::Address address, uint32_t value);

    Settings::Range GetRange(Settings::Address address) const;

    // Factory reset
    void WriteDefaultSettings();

    // non-copyable & non-movable
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;
    SettingsManager(SettingsManager&&) = delete;
    SettingsManager& operator=(SettingsManager&&) = delete;

private:
    void WriteByte(Settings::Address address, uint8_t value);
    uint8_t ReadByte(Settings::Address address) const;
    void WriteShort(Settings::Address address, uint16_t value);
    uint16_t ReadShort(Settings::Address address) const;
};