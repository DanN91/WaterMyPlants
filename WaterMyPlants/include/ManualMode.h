/*
    ...
*/

#pragma once

#include <WaterPump.h>
#include <PushButtonMasks.h>

#include <ObserverPattern.h>
#include <IOperationMode.h>

class ManualMode final : public IObserver<ButtonState>, public IOperationMode
{
public:
    ManualMode(WaterPump& waterPump, IObservable<ButtonState>& button);
    ~ManualMode();

    // IObserver
    void OnEvent(ButtonState event) override;

    // IOperationMode
    void Run() override;
    void Activate() override;
    void Deactivate() override;

private:
    WaterPump& m_waterPump;
    uint32_t m_lastOn = 0;
};