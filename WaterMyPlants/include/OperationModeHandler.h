/*
    ...
*/

#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>

#include <PushButton.h>
#include <RangeValuesGenerator.h>
#include <WaterPump.h>
#include <PersistenceManager.h>

class IOperationMode;

enum class OperationMode : uint8_t
{
    Manual = 0,
    Timer,
    Sensor,
    None // must be the last
};

class OperationModeHandler final : public IObserver<ButtonState>
{
public:
    explicit OperationModeHandler(IObservable<ButtonState>& subject, PersistenceManager& persistence);
    ~OperationModeHandler();

    void Initialize() const;
    void Run();

    // IObserver
    void OnEvent(ButtonState event) override;

    // non-copyable & non-movable
    OperationModeHandler(const OperationModeHandler&) = delete;
    OperationModeHandler& operator=(const OperationModeHandler&) = delete;
    OperationModeHandler(OperationModeHandler&&) = delete;
    OperationModeHandler& operator=(OperationModeHandler&&) = delete;

private:
    void SetOperationMode(OperationMode operationMode);

    IOperationMode* m_operation = nullptr;

    RangeValuesGenerator m_generator;
    PersistenceManager& m_persistence;

    // hardware
    WaterPump m_waterPump;
    PushButton m_executionButton;
};