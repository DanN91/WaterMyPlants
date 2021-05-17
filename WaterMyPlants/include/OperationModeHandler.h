/*
    ...
*/

#pragma once

#include <Arduino.h>

#include <UniquePtr.h>
#include <ObserverPattern.h>

#include <PushButton.h>
#include <RangeValuesGenerator.h>
#include <WaterPump.h>

class SettingsManager;
class IOperationMode;

enum class OperationMode : uint8_t
{
    Manual = 0,
    Timer,
    Sensor,
    None, // this should be last
};

class OperationModeHandler final : public IObserver<ButtonState>
{
public:
    explicit OperationModeHandler(IObservable<ButtonState>& subject, PushButton& executionButton, SettingsManager& settings);
    ~OperationModeHandler() = default;

    void Initialize() const;
    void Run();

    OperationMode CurrentMode() const;

    // IObserver
    void OnEvent(ButtonState event) override;

    // non-copyable & non-movable
    OperationModeHandler(const OperationModeHandler&) = delete;
    OperationModeHandler& operator=(const OperationModeHandler&) = delete;
    OperationModeHandler(OperationModeHandler&&) = delete;
    OperationModeHandler& operator=(OperationModeHandler&&) = delete;

private:
    void SetOperationMode(OperationMode operationMode);

    UniquePtr<IOperationMode> m_operation;
    OperationMode m_currentMode = OperationMode::None;

    RangeValuesGenerator m_generator;
    SettingsManager& m_settings;

    // hardware
    WaterPump m_waterPump;
    PushButton& m_executionButton;
};