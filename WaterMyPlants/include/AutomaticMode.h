/*
    ...
*/

#pragma once

#include <WaterPump.h>

#include <IOperationMode.h>

class AutomaticMode final : public IOperationMode
{
public:
    AutomaticMode(WaterPump& waterPump);

    // IOperationMode
    void Run() override;

private:
    WaterPump& m_waterPump;
};