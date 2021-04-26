/*
    ...
*/

#pragma once

#include <Arduino.h>

class NokiaDisplay;
class MenuItem;
class SettingsManager;
class StringsManager;
class PushButton;

class ChangeSetting final
{
public:
    ChangeSetting(NokiaDisplay& display, MenuItem& item, SettingsManager& settings, StringsManager& strings, PushButton& button);
    ~ChangeSetting() = default;

    void Execute();

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
    PushButton& m_button;
};