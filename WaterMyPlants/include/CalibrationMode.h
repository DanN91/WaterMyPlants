/*
    Author: Daniel Nistor
    Purpose: Decorator over ManualMode responsible with allowing the user to set the watering time via start-stop and storing that value persistently for further usage.
    MIT License, 2021
*/

#pragma once

#include <IOperationMode.h>
#include <ManualMode.h>

class CalibrationMode final : public IOperationMode
{
public:
    CalibrationMode(ManualMode& manualMode);

    // IOperationMode
    void Run() override;

private:
    ManualMode& m_manualMode;
};