/*
    ...
*/

#include "PushButton.h"

namespace
{
    constexpr const uint16_t DEBOUNCE_DELAY_MS = 50;
    constexpr const uint16_t HELD_THRESHOLD_MS = 1000;
} // anonymous

PushButton::PushButton(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT)
    : IObservable(MAX_OBSERVERS_COUNT)
    , m_pin(pin)
{
}

void PushButton::Initialize() const
{
    pinMode(m_pin, INPUT);
}

void PushButton::HandleEvents()
{
    volatile bool reading = digitalRead(m_pin);

    if (reading != m_lastButtonState)
        m_lastDebounceTime = millis();

    if ((millis() - m_lastDebounceTime) > DEBOUNCE_DELAY_MS)
    {
        if (reading != m_lastReading)
        {
            m_lastReading = reading;

            if (m_lastReading == LOW)
            {
                if ((millis() - m_lastPressedTime) >= HELD_THRESHOLD_MS)
                {
                    // Serial.println("BTN:Held");
                    Notify(ButtonState::Held);
                }
                else
                {
                    // Serial.println("BTN:Released");
                    Notify(ButtonState::Released);
                }
            }
            else
            {
                // Serial.println("BTN:Pressed");
                Notify(ButtonState::Pressed);
                m_lastPressedTime = millis();
            }
        }
    }

    m_lastButtonState = reading;
}