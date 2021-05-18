/*
    ChangeSetting: allows user interaction for changing the value of a setting and storing it into persistence.
    Author: Daniel Nistor
    MIT License, 2021
*/
#include "ChangeSetting.h"

#include <NokiaDisplay.h>
#include <Menu.h>

ChangeSetting::ChangeSetting(NokiaDisplay& display, const Menu& menu, uint8_t itemIndex, IObservable<ButtonState>& button)
    : IObserver(ButtonState::Released | ButtonState::Held, button)
    , m_itemIndex(itemIndex)
    , m_menuItem(*menu.GetMenuItem(m_itemIndex))
    , m_generator({ m_settings.GetRange(m_menuItem.Value()).Min(), m_settings.GetRange(m_menuItem.Value()).Max() }, m_settings.GetRange(m_menuItem.Value()).Step(), m_settings.Read(m_menuItem.Value()), button, ButtonState::Released)
    , m_display(display)
{
    button.Register(&m_generator);
    button.Register(this);
}

ChangeSetting::~ChangeSetting()
{
    UpdateItem(m_settings.Read(m_menuItem.Value()));
}

void ChangeSetting::OnEvent(ButtonState event)
{
    switch (event)
    {
        case ButtonState::Released:
        {
            UpdateItem(m_generator.Value());
            break;
        }

        case ButtonState::Held:
        {
            m_settings.Write(m_menuItem.Value(), m_generator.Value());
            break;
        }
    }
}

void ChangeSetting::UpdateItem(uint32_t value)
{
    const uint8_t itemLineIndex = 2 + m_itemIndex;

    m_display.SetCursor(itemLineIndex, 0);
    m_display.ClearLine();
    m_display.Write(itemLineIndex, m_strings.Read(m_menuItem.Text()), NokiaDisplay::Aligned::Left);
    m_display.Write(itemLineIndex, value, NokiaDisplay::Aligned::Right);
}
