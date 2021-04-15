/*
    ...
*/

#include "OperationModeHandler.h"

#include <Hardware.h>

#include <IOperationMode.h>
#include <ManualMode.h>
#include <CalibrationMode.h>
#include <TimerMode.h>
// #include <SensorMode.h>

namespace
{
    const char* GetOperationStr(OperationMode operationMode)
    {
        switch (operationMode)
        {
            case OperationMode::Manual:
                return "Manual";

            case OperationMode::Calibration:
                return "Calibration";

            case OperationMode::Timer:
                return "Timer";

            case OperationMode::Sensor:
                return "Sensor";
        }

        return "Not found";
    }
} // anonymous

OperationModeHandler::OperationModeHandler(OperationMode defaultMode, IObservable<ButtonState>& subject)
    : IObserver(ButtonState::Pressed, subject)
    , m_waterPump(Hardware::WATER_PUMP_PIN)
    , m_executionButton(Hardware::EXECUTION_BUTTON_PIN, 3)
{
    SetOperationMode(defaultMode);
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
    if (m_current == operationMode)
        return; // nothing to change

    // release memory for current mode
    if (m_operation)
        delete m_operation;

    m_current = operationMode;

    Serial.println(GetOperationStr(m_current));

    switch (operationMode)
    {
        case OperationMode::Manual:
        {
            m_operation = new ManualMode(m_waterPump, m_executionButton);
            break;
        }

        case OperationMode::Calibration:
        {
            m_operation = new CalibrationMode(m_waterPump, m_executionButton);
            break;
        }

        case OperationMode::Timer:
        {
            m_operation = new TimerMode(m_waterPump);
            break;
        }

        case OperationMode::Sensor:
        {
            // #DNN:ToDo
            m_operation = nullptr;
            break;
        }

        case OperationMode::None:
        {
            m_operation = nullptr;
            break;
        }
    }
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
    {
        static auto modeCounter = static_cast<uint8_t>(m_current);

        modeCounter++; // next operation mode
        modeCounter = modeCounter % static_cast<uint8_t>(OperationMode::None);

        SetOperationMode(static_cast<OperationMode>(modeCounter));
    }
}