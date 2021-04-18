/*
    ...
*/

#include "OperationModeHandler.h"

#include <Hardware.h>

#include <IOperationMode.h>
#include <ManualMode.h>
#include <TimerMode.h>
// #include <SensorMode.h>

OperationModeHandler::OperationModeHandler(IObservable<ButtonState>& subject, PersistenceManager& persistence)
    : IObserver(ButtonState::Pressed, subject)
    , m_generator(0, static_cast<uint8_t>(OperationMode::None) - 1, subject)
    , m_persistence(persistence)
    , m_waterPump(Hardware::WATER_PUMP_PIN)
    , m_executionButton(Hardware::EXECUTION_BUTTON_PIN, 3)
{
    if (const auto lastOperationMode = m_persistence.LastOperationMode(); lastOperationMode < static_cast<uint8_t>(OperationMode::None))
        SetOperationMode(static_cast<OperationMode>(lastOperationMode));
}

OperationModeHandler::~OperationModeHandler()
{
    if (m_operation)
        delete m_operation;
}

void OperationModeHandler::Initialize() const
{
    m_waterPump.Initialize();
    m_executionButton.Initialize();
}

void OperationModeHandler::SetOperationMode(OperationMode operationMode)
{
    // release memory for current mode
    if (m_operation)
    {
        delete m_operation;
        m_operation = nullptr;
    }

    switch (operationMode)
    {
        case OperationMode::Manual:
        {
            m_operation = new ManualMode(m_waterPump, m_executionButton);
            break;
        }

        case OperationMode::Timer:
        {
            m_operation = new TimerMode(m_waterPump, m_persistence);
            break;
        }

        case OperationMode::Sensor:
        {
            // #DNN:ToDo
            m_operation = nullptr;
            break;
        }
    }

    m_persistence.LastOperationMode(static_cast<uint8_t>(operationMode));
}

void OperationModeHandler::Run()
{
    m_executionButton.HandleEvents();

    if (m_operation)
        m_operation->Run();
}

void OperationModeHandler::OnEvent(ButtonState event)
{
    if (event == ButtonState::Pressed)
        SetOperationMode(static_cast<OperationMode>(m_generator.Value()));
}