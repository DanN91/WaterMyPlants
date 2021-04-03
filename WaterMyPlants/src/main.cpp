#include <Arduino.h>

#include <TogglePushButton.h>
#include <WaterPump.h>

constexpr const uint8_t PUMP_PIN = 0;   // 13, Arduino Uno
constexpr const uint8_t BUTTON_PIN = 1; // 8, Arduino Uno

class IOperationMode
{
public:
    virtual void Run() = 0;
};

class ManualMode final : public IPushButtonObserver, public IOperationMode
{
public:
    ManualMode(WaterPump& waterPump) : m_waterPump(waterPump) {}

    // IPushButtonObserver
    void WasPressed() override
    {
        m_waterPump.IsOn() ? m_waterPump.TurnOff() : m_waterPump.TurnOn();

        if (m_waterPump.IsOn())
            m_lastOn = millis();
    }

    // IOperationMode
    void Run() override
    {
        // safeguard against too much water
        if (m_waterPump.IsOn() && (millis() - m_lastOn) > MAX_ON_TIME_LIMIT_MS)
            m_waterPump.TurnOff();
    }

private:
    static constexpr uint32_t MAX_ON_TIME_LIMIT_MS = 90000u; // 90 seconds should suffice

    WaterPump& m_waterPump;
    uint32_t m_lastOn = 0;
};

class AutomaticMode final : public IOperationMode
{
public:
    AutomaticMode(WaterPump& waterPump) : m_waterPump(waterPump) {}

    // IOperationMode
    void Run() override
    {

    }

private:
    WaterPump& m_waterPump;
};

WaterPump waterPump(PUMP_PIN);

ManualMode attended(waterPump);
AutomaticMode unattended(waterPump);

TogglePushButton button(BUTTON_PIN, attended);

boolean isTest = false;

const uint32_t SECOND_MS = 1350u;
const uint32_t MINUTE_MS = 60 * SECOND_MS;
const uint32_t HOUR_MS = (isTest) ? SECOND_MS : 60 * MINUTE_MS * SECOND_MS;
const uint32_t DAY_MS = (isTest) ? 5 * HOUR_MS : 24 * HOUR_MS;

const uint32_t TIME_TO_WATER_MS = (isTest) ? 3 * SECOND_MS : 2 * DAY_MS;
const uint32_t WATERING_TIME_MS = (isTest) ? 10 * SECOND_MS : MINUTE_MS;

// boolean isUnattended = true;

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

void setup()
{
    // initialize hardware components
    waterPump.Initialize();
    button.Initialize();
}

void loop()
{
    button.HandleEvents();
    // ManualMode(BUTTON_PIN, PUMP_PIN);
    // if (isUnattended)
    //   AutomaticMode(PUMP_PIN);
}