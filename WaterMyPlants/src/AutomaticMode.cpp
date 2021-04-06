/*
    ...
*/

#include "AutomaticMode.h"

AutomaticMode::AutomaticMode(WaterPump &waterPump)
    : m_waterPump(waterPump)
{
}

void AutomaticMode::Run()
{
    // ...
    // static uint32_t previousMillis = millis();

    // void AutomaticMode(byte pumpPin)
    // {
    //   const uint32_t currentMillis = millis();
    //   if ((uint32_t)(currentMillis - previousMillis) >= TIME_TO_WATER_MS)
    //   {
    //     // pump ON
    //     digitalWrite(pumpPin, HIGH);
    //     Debug("Auto: Pump ON");

    //     const uint32_t wateringStartedMillis = millis();
    //     do
    //     {
    //         // make space for aborting automatic watering
    //         const bool doAbort = GetButtonState(BUTTON_PIN);
    //         if (doAbort)
    //         {
    //           // stop pump immediately, give control to user
    //           isUnattended = false;
    //           ResetButtonState();
    //           break;
    //         }
    //     } while ((uint32_t)(millis() - wateringStartedMillis) < WATERING_TIME_MS);

    //     // pump OFF
    //     digitalWrite(pumpPin, LOW);
    //     Debug("Auto: Pump OFF");

    //     // start counting from now on
    //     if (isUnattended)
    //     {
    //       Debug("Auto: Wait to water again...");
    //     }
    //     else
    //     {
    //       Debug("Auto: Switched to Manual mode");
    //     }

    //     previousMillis = millis();
    //   }
    // }
}