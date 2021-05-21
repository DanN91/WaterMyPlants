/*
    ChangeSetting: allows user interaction for changing the value of a setting and storing it into persistence.
    Author: Daniel Nistor
    MIT License, 2021
*/
#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include <PushButtonMasks.h>
#include <SettingMenuItem.h>
#include <RangeValuesGenerator.h>
#include <SettingsManager.h>
#include <StringsManager.h>
#include <IMenu.h>

class NokiaDisplay;

class ChangeSetting final : public IObserver<ButtonState>
{
public:
    ChangeSetting(NokiaDisplay& display, const IMenu& menu, uint8_t itemIndex, IObservable<ButtonState>& button);
    ~ChangeSetting();

    // IObserver
    void OnEvent(ButtonState event);

    // non-copyable & non-movable
    ChangeSetting(const ChangeSetting&) = delete;
    ChangeSetting& operator=(const ChangeSetting&) = delete;
    ChangeSetting(ChangeSetting&&) = delete;
    ChangeSetting& operator=(ChangeSetting&&) = delete;

private:
    void UpdateItem(uint32_t value);

    StringsManager m_strings;

    const uint8_t m_itemIndex;
    const IMenuItem& m_menuItem;
    Settings::Address m_address;

    RangeValuesGenerator m_generator;
    NokiaDisplay& m_display;
};