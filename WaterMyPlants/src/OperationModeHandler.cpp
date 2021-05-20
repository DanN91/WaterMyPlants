/*
    OperationModeHandler: iterates through available operation modes whenever the observed push button is released.
    Author: Daniel Nistor
    MIT License, 2021
*/
#include "OperationModeHandler.h"

OperationModeHandler::OperationModeHandler(IObservable<ButtonState>& subject, SettingsManager& settings)
    : IObserver(ButtonState::Released, subject)
    , m_currentModeIndex(settings.Read(Settings::Address::LastOperationMode))
    , m_generator({ 0, 0 }, 1, m_currentModeIndex, subject) // range is set in Initialize, after operation modes have been added
    , m_settings(settings)
{
    subject.Register(&m_generator);
    subject.Register(this);
}

void OperationModeHandler::Initialize()
{
    OnEvent(ButtonState::Released);
}

void OperationModeHandler::Run()
{
    if (const auto currentMode = m_operationModes[m_currentModeIndex])
        (*currentMode)->Run();
}

void OperationModeHandler::Add(IOperationMode& operationMode)
{
    m_operationModes.Add(&operationMode);
    UpdateRange();
}

void OperationModeHandler::Remove(uint8_t index)
{
    m_operationModes.Remove(index);
    UpdateRange();
}

void OperationModeHandler::SetOperationMode(uint8_t operationModeIndex)
{
    if (const auto currentMode = m_operationModes[m_currentModeIndex]) // deactivate previous
        (*currentMode)->Deactivate();

    if (const auto nextMode = m_operationModes[operationModeIndex]) // activate current
        (*nextMode)->Activate();

    m_currentModeIndex = operationModeIndex;
    m_settings.Write(Settings::Address::LastOperationMode, m_currentModeIndex);
}

uint8_t OperationModeHandler::CurrentModeIndex() const
{
    return m_currentModeIndex;
}

void OperationModeHandler::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
        SetOperationMode(m_generator.Value());
}

void OperationModeHandler::UpdateRange()
{
    m_generator.Range({ 0, m_operationModes.Size() ? (m_operationModes.Size() - 1) : 0 }, m_currentModeIndex);
}