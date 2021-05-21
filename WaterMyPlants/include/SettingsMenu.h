/*
    SettingsMenu: Menu handling settings items.
    Author: Daniel Nistor
    MIT License, 2021
*/
#pragma once

#include <Arduino.h>

#include <Vector.h>
#include <IMenu.h>
#include <StringsManager.h>
#include <SettingMenuItem.h>

class SettingsMenu final : public IMenu
{
public:
    SettingsMenu(Strings::Address titleAddress);
    ~SettingsMenu() = default;

    void AddMenuItem(const SettingMenuItem& item);

    // IMenu
    const IMenuItem* GetMenuItem(uint8_t index) const override;
    uint8_t ItemsCount() const override;
    void HandleItem(uint8_t itemIndex) override;

private:
    Vector<SettingMenuItem> m_items;
};
