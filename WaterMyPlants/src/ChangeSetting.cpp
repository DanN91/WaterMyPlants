/*
    ...
*/

#include "ChangeSetting.h"

#include <NokiaDisplay.h>
#include <MenuItem.h>
#include <SettingsManager.h>
#include <StringsManager.h>
#include <PushButton.h>

ChangeSetting::ChangeSetting(NokiaDisplay& display, MenuItem& item, SettingsManager& settings, StringsManager& strings, IObservable<ButtonState>& button)
    : IObserver(ButtonState::Released | ButtonState::Held, button)
    , m_display(display)
    , m_item(item)
    , m_settings(settings)
    , m_strings(strings)
    , m_generator({ m_settings.GetRange(m_item.Value()).Min(), m_settings.GetRange(m_item.Value()).Max() }, m_settings.GetRange(m_item.Value()).Step(), m_settings.Read(m_item.Value()), button, ButtonState::Released)
{
}

void ChangeSetting::OnEvent(ButtonState event)
{
    Serial.print("[");
    Serial.print(m_settings.GetRange(m_item.Value()).Min());
    Serial.print(" - ");
    Serial.print(m_settings.GetRange(m_item.Value()).Max());
    Serial.println("]");

    switch (event)
    {
        case ButtonState::Released:
        {
            Serial.print("CS: Released: ");
            Serial.println(m_generator.Value());
            break;
        }

        case ButtonState::Held:
        {
            Serial.print("CS: Held: ");
            Serial.println(m_generator.Value());

            m_settings.Write(m_item.Value(), m_generator.Value());
            break;
        }
    }
}
