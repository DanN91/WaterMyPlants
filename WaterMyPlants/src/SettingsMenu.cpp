/*
    SettingsMenu: Menu handling settings items.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(Strings::Address titleAddress)
    : IMenu(titleAddress)
{}

void SettingsMenu::AddMenuItem(const SettingMenuItem& item)
{
    return m_items.Add(item);
}

// IMenu
inline const IMenuItem* SettingsMenu::GetMenuItem(uint8_t index) const
{
    return m_items[index];
}

inline uint8_t SettingsMenu::ItemsCount() const
{
    return m_items.Size();
}

void SettingsMenu::HandleItemChange(uint8_t itemIndex)
{
    m_changeSetting.Reset(new ChangeSetting(m_display, (*m_menu), m_cursor.Value(), m_execution));
}