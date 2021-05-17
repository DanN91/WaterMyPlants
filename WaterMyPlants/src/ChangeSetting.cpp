/*
    ...
*/

#include "ChangeSetting.h"

#include <SettingsManager.h>

ChangeSetting::ChangeSetting(SettingsManager& settings, const MenuItem& item, IObservable<ButtonState>& button)
    : IObserver(ButtonState::Held, button)
    , m_item(item)
    , m_settings(settings)
    , m_generator({ m_settings.GetRange(m_item.Value()).Min(), m_settings.GetRange(m_item.Value()).Max() }, m_settings.GetRange(m_item.Value()).Step(), m_settings.Read(m_item.Value()), button, ButtonState::Released)
{
    // lazy registering for better ordering flexibility
    button.Register(&m_generator);
    button.Register(this);
}

void ChangeSetting::OnEvent(ButtonState event)
{
    if (event == ButtonState::Held)
        m_settings.Write(m_item.Value(), m_generator.Value());
}
