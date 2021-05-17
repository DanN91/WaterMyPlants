/*
    ...
*/

#include "OperationModeHandler.h"

#include <Hardware.h>
#include <SettingsManager.h>

#include <IOperationMode.h>
#include <ManualMode.h>
#include <TimerMode.h>
// #include <SensorMode.h>

OperationModeHandler::OperationModeHandler(IObservable<ButtonState>& subject, PushButton& executionButton, SettingsManager& settings)
    : IObserver(ButtonState::Released, subject)
    , m_operation(nullptr)
    , m_generator({ 0, static_cast<uint8_t>(OperationMode::None) - 1 }, 1, settings.Read(Settings::Address::LastOperationMode), subject)
    , m_settings(settings)
    , m_waterPump(Hardware::WATER_PUMP_PIN)
    , m_executionButton(executionButton)
{
    subject.Register(&m_generator);
    subject.Register(this);

    OnEvent(ButtonState::Released);
}

void OperationModeHandler::Initialize() const
{
    m_waterPump.Initialize();
}

void OperationModeHandler::SetOperationMode(OperationMode operationMode)
{
    m_currentMode = operationMode;

    switch (m_currentMode)
    {
        case OperationMode::Manual:
        {
            m_operation.Reset(new ManualMode(m_waterPump, m_executionButton));
            break;
        }

        case OperationMode::Timer:
        {
            m_operation.Reset(new TimerMode(m_waterPump, m_settings));
            break;
        }

        case OperationMode::Sensor:
        {
            // #DNN:ToDo
            m_operation.Reset(nullptr);
            break;
        }
    }

    m_settings.Write(Settings::Address::LastOperationMode, static_cast<uint8_t>(operationMode));
}

void OperationModeHandler::Run()
{
    m_executionButton.HandleEvents();

    if (m_operation)
        m_operation->Run();
}

OperationMode OperationModeHandler::CurrentMode() const
{
    return m_currentMode;
}

void OperationModeHandler::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
        SetOperationMode(static_cast<OperationMode>(m_generator.Value()));
}