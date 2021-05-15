/*
    StringsManager: wrapper over EEPROM which aids in writing and reading strings from EEPROM.
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

    constexpr const auto SEPARATOR = "--------------";

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

enum class Language
{
    English,
    Romanian
};

class StringsManager final
{
public:
    StringsManager(Language language = Language::English);
    ~StringsManager() = default;

    String Read(Strings::Address address) const;

    // this should be called once and then the code commented and recompiled + reuploaded to avoid wasting EEPROM cycles
    void WriteAllStrings();

    // non-copyable & non-movable
    StringsManager(const StringsManager&) = delete;
    StringsManager& operator=(const StringsManager&) = delete;
    StringsManager(StringsManager&&) = delete;
    StringsManager& operator=(StringsManager&&) = delete;

private:
    void Write(Strings::Address address, const char *text);

    const Language m_language; // #DNN:ToDo:changeable at run-time?
};