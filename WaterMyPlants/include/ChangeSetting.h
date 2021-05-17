/*
    ...
*/

#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include <PushButtonMasks.h>
#include <MenuItem.h>
#include <RangeValuesGenerator.h>

class SettingsManager;

class ChangeSetting final : public IObserver<ButtonState>
{
public:
    ChangeSetting(SettingsManager& settings, const MenuItem& item, IObservable<ButtonState>& button);
    ~ChangeSetting() = default;

    // IObserver
    void OnEvent(ButtonState event);

    // non-copyable & non-movable
    ChangeSetting(const ChangeSetting&) = delete;
    ChangeSetting& operator=(const ChangeSetting&) = delete;
    ChangeSetting(ChangeSetting&&) = delete;
    ChangeSetting& operator=(ChangeSetting&&) = delete;

private:
    const MenuItem& m_item;
    SettingsManager& m_settings;
    RangeValuesGenerator m_generator;
};