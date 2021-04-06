/*
    Author: Daniel Nistor
    Purpose: Component responsible with allowing the user to set the watering time via start-stop and storing that value persistently for further usage.
    MIT License, 2021
*/

#include "CalibrationMode.h"

#include <EEPROM.h>

CalibrationMode::CalibrationMode(ManualMode& manualMode)
    : m_manualMode(manualMode)
{
}

void CalibrationMode::Run()
{

}