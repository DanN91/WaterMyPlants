/*
    ...
*/

#pragma once

#include <Arduino.h>
#include <ObserverPattern.h>
#include <PushButtonMasks.h>
#include <RangeValuesGenerator.h>

class NokiaDisplay;
class MenuItem;
class StringsManager;
class SettingsManager;

class ChangeSetting final : public IObserver<ButtonState>
{
public:
    ChangeSetting(NokiaDisplay& display, MenuItem& item, SettingsManager& settings, StringsManager& strings, IObservable<ButtonState>& button);
    ~ChangeSetting() = default;

    // IObserver
    void OnEvent(ButtonState event);

    // non-copyable & non-movable
    ChangeSetting(const ChangeSetting&) = delete;
    ChangeSetting& operator=(const ChangeSetting&) = delete;
    ChangeSetting(ChangeSetting&&) = delete;
    ChangeSetting& operator=(ChangeSetting&&) = delete;

private:
    NokiaDisplay& m_display;
    MenuItem& m_item;
    SettingsManager& m_settings;
    StringsManager& m_strings;
    RangeValuesGenerator m_generator;
};