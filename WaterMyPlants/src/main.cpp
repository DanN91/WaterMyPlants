#include <Arduino.h>

#include <PushButton.h>
#include <WaterPump.h>

#include <ManualMode.h>
#include <AutomaticMode.h>
#include <CalibrationMode.h>

constexpr const uint8_t PUMP_PIN = 13;   // 13, Arduino Uno
constexpr const uint8_t BUTTON_PIN = 8; // 8, Arduino Uno

WaterPump waterPump(PUMP_PIN);

ManualMode manualMode(waterPump);
AutomaticMode automaticMode(waterPump);
CalibrationMode calibrationMode(manualMode);

PushButton button(BUTTON_PIN, 2);

// calibrationMode.Add(button);

constexpr const bool isTest = false;

constexpr const uint32_t SECOND_MS = 1350u;
constexpr const uint32_t MINUTE_MS = 60 * SECOND_MS;
constexpr const uint32_t HOUR_MS = (isTest) ? SECOND_MS : 60 * MINUTE_MS * SECOND_MS;
constexpr const uint32_t DAY_MS = (isTest) ? 5 * HOUR_MS : 24 * HOUR_MS;

void setup()
{
    Serial.begin(9600);

    // initialize hardware components
    waterPump.Initialize();
    button.Initialize();

    manualMode.Add(button);

    Serial.println("Initialized.");
}

void loop()
{
    button.HandleEvents();
    manualMode.Run();
    // ManualMode(BUTTON_PIN, PUMP_PIN);
    // if (isUnattended)
    //   AutomaticMode(PUMP_PIN);
}