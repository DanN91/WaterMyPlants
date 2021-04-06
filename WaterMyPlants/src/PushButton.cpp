/*
    ...
*/

#include "PushButton.h"

PushButton::PushButton(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT)
    : IObservable(MAX_OBSERVERS_COUNT)
    , m_pin(pin)
{
}

void PushButton::Initialize() const { pinMode(m_pin, INPUT); }

void PushButton::HandleEvents()
{
    constexpr const uint16_t DEBOUNCE_DELAY = 50;

    static bool m_buttonState = false;
    static bool lastButtonState = false;
    static uint32_t lastDebounceTime = 0;

    const bool reading = digitalRead(m_pin);

    if (reading != lastButtonState)
        lastDebounceTime = millis();

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
    {
        if (reading != m_buttonState)
        {
            m_buttonState = reading;

            if (m_buttonState == LOW)
                Notify(static_cast<uint16_t>(ButtonState::Clicked));
        }
    }

    lastButtonState = reading;
}