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
        constexpr const uint32_t HOUR_MS = 60 * MINUTE_MS;
        constexpr const uint32_t DAY_MS = 24 * HOUR_MS;
    }
}