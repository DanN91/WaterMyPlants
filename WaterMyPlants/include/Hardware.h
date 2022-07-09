/*
    ...
*/

#pragma once

#include <Arduino.h>

namespace Hardware
{
    constexpr uint8_t SOIL_MOISTURE_SENSOR_PIN = A0;
    constexpr uint8_t LIGHT_SENSOR_PIN = A1;

    constexpr uint8_t WATER_PUMP_PIN = 8;
    constexpr uint8_t MODE_CHANGER_BUTTON_PIN = 2;
    constexpr uint8_t EXECUTION_BUTTON_PIN = 3;
    constexpr uint8_t MENU_NAVIGATION_BUTTON_PIN = 4;

    constexpr uint8_t NOKIA_RESET_PIN = 13;
    constexpr uint8_t NOKIA_CHIP_ENABLE_PIN = 12;
    constexpr uint8_t NOKIA_DATA_SELECT_PIN = 11;
    constexpr uint8_t NOKIA_DATA_IN_PIN = 10;
    constexpr uint8_t NOKIA_CLOCK_PIN = 9;
}