/*
    ...
*/

#pragma once

#include <Arduino.h>

namespace Constants
{
    constexpr const uint8_t WATERING_TIME_SEC_ADDRESS = 0x20; // 32
    constexpr const uint8_t MAX_WATERING_TIME_SEC = 120;

    constexpr const bool isTest = true;

    constexpr const uint32_t SECOND_MS = 1000u;
    constexpr const uint32_t MINUTE_MS = 60 * SECOND_MS;
    constexpr const uint32_t HOUR_MS = (isTest) ? SECOND_MS : 60 * MINUTE_MS * SECOND_MS;
    constexpr const uint32_t DAY_MS = (isTest) ? 5 * HOUR_MS : 24 * HOUR_MS;

    constexpr const auto TIME_TO_WATER_MS = DAY_MS * 2;
}