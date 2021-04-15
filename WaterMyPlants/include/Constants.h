/*
    ...
*/

#pragma once

#include <Arduino.h>

namespace Constants
{
    // TIME
    namespace Time
    {
        constexpr const uint32_t SECOND_MS = 1000u;
        constexpr const uint32_t MINUTE_MS = 60 * SECOND_MS;
        constexpr const uint32_t HOUR_MS = 60 * MINUTE_MS * SECOND_MS;
        constexpr const uint32_t DAY_MS = 24 * HOUR_MS;
    }

    // EEPROM ADDRESSES
    namespace Addresses
    {
        constexpr const uint8_t WATERING_DURATION_SECONDS = 0x20; // 32, 2 bytes
        constexpr const uint8_t WATERING_FREQUENCY_MINUTES = 0x22; // 34, 2 bytes
    }

    // OTHER
    constexpr const auto TIME_TO_WATER_MS = 30 * SECOND_MS;
}