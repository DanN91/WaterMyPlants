/*
    PersistenceManager: wrapper over EEPROM which aids in writing and reading data from EEPROM.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

// Sector in EEPROM
namespace Strings
{
    constexpr uint16_t STRINGS_BEGIN = 200;
    constexpr uint16_t STRINGS_END = 500;
    constexpr const uint8_t SPACE_BETWEEN_STRINGS = 1;

    constexpr auto SEPARATOR = "--------------";

    namespace ENU
    {
        // Operation Modes
        constexpr const auto MANUAL_MODE_TITLE = "Manual";
        constexpr const auto TIMER_MODE_TITLE = "Timer";
        constexpr const auto SENSOR_MODE_TITLE = "Sensor";

        // Timer Mode
        constexpr const auto TIMER_MODE_CALIBRATION_DURATION = "Duration";
        constexpr const auto TIMER_MODE_CALIBRATION_FREQUENCY = "Frequency";

        // Sensor Mode
        constexpr const auto SENSOR_MODE_DRY = "Dry";
        constexpr const auto SENSOR_MODE_WET = "Wet";
    }

    namespace ROM
    {
        // #TODO
    }

    enum class Address : uint16_t
    {
        // Operation Modes
        TitleSeparator = STRINGS_BEGIN,
        ManualModeTitle = TitleSeparator + strlen(SEPARATOR) + SPACE_BETWEEN_STRINGS,
        TimerModeTitle = ManualModeTitle + strlen(ENU::MANUAL_MODE_TITLE) + SPACE_BETWEEN_STRINGS,
        SensorModeTitle = TimerModeTitle + strlen(ENU::TIMER_MODE_TITLE) + SPACE_BETWEEN_STRINGS,

        // Timer Mode
        TimerModeDuration = SensorModeTitle + strlen(ENU::SENSOR_MODE_TITLE) + SPACE_BETWEEN_STRINGS,
        TimerModeFrequency = TimerModeDuration + strlen(ENU::TIMER_MODE_CALIBRATION_DURATION) + SPACE_BETWEEN_STRINGS,

        // Sensor Mode
        SensorModeDry = TimerModeFrequency + strlen(ENU::TIMER_MODE_CALIBRATION_FREQUENCY) + SPACE_BETWEEN_STRINGS,
        SensorModeWet = SensorModeDry + strlen(ENU::SENSOR_MODE_DRY) + SPACE_BETWEEN_STRINGS,

        // Not found, invalid address
        Invalid = SensorModeWet + strlen(ENU::SENSOR_MODE_WET) + SPACE_BETWEEN_STRINGS, // empty ""
    };
}

namespace Settings
{
    constexpr uint16_t SETTINGS_BEGIN = 0;
    constexpr uint16_t SETTINGS_END = 100;

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

    struct Limits
    {
    public:
        Limits(uint16_t min, uint16_t max)
            : m_min(min),
              m_max(max)
        {}

    private:
        const uint16_t m_min = 0;
        const uint16_t m_max = 0;
    };
}

class PersistenceManager final
{
public:
    PersistenceManager() = default;
    ~PersistenceManager() = default;

	String Get(Strings::Address stringAddress) const;
	uint32_t Get(Settings::Address settingAddress) const;
	
    // Settings
    uint16_t TimerModeDuration() const;
	void TimerModeDuration(uint16_t seconds);

	uint8_t TimerModeFrequency() const;
	void TimerModeFrequency(uint8_t days);

    uint8_t SensorModeDry() const;
	void SensorModeDry(uint8_t percent);

	uint8_t SensorModeWet() const;
	void SensorModeWet(uint8_t percent);

    uint8_t LastOperationMode() const;
    void LastOperationMode(uint8_t modeIndex);

	void WriteAllStrings();
    void WriteDefaultSettings();

private:
	void Write(Strings::Address address, const char* text);
    void WriteByte(Settings::Address address, uint8_t value);
    uint8_t ReadByte(Settings::Address address) const;

	// non-copyable & non-movable
    PersistenceManager(const PersistenceManager&) = delete;
	PersistenceManager& operator=(const PersistenceManager&) = delete;
    PersistenceManager(PersistenceManager&&) = delete;
	PersistenceManager& operator=(PersistenceManager&&) = delete;
};