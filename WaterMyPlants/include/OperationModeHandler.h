/*
    OperationModeHandler: iterates through available operation modes whenever the observed push button is released.
    Author: Daniel Nistor
    MIT License, 2021
*/
#pragma once

#include <Arduino.h>

#include <Vector.h>
#include <ObserverPattern.h>

#include <PushButton.h>
#include <RangeValuesGenerator.h>

#include <SettingsManager.h>
#include <IOperationMode.h>

class OperationModeHandler final : public IObserver<ButtonState>
{
public:
    explicit OperationModeHandler(IObservable<ButtonState>& subject);
    ~OperationModeHandler() = default;

    void Initialize();
    void Run();

    void Add(IOperationMode& operationMode);
    void Remove(uint8_t index);

    void SetOperationMode(uint8_t operationModeIndex);
    uint8_t CurrentModeIndex() const;

    // IObserver
    void OnEvent(ButtonState event) override;

    // non-copyable & non-movable
    OperationModeHandler(const OperationModeHandler&) = delete;
    OperationModeHandler& operator=(const OperationModeHandler&) = delete;
    OperationModeHandler(OperationModeHandler&&) = delete;
    OperationModeHandler& operator=(OperationModeHandler&&) = delete;

private:
    void UpdateRange();

    Vector<IOperationMode*> m_operationModes;
    uint8_t m_currentModeIndex = 0;

    RangeValuesGenerator m_generator;
};