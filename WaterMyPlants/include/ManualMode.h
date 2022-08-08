/*
    ...
*/

#pragma once

#include <WaterPump.h>

#include <ObserverPattern.h>
#include <PushButtonMasks.h>
#include <TimerManagerMasks.h>
#include <IOperationMode.h>

class ManualMode final : public IObserver<ButtonState>, public IObserver<TimerEvent>, public IOperationMode
{
public:
    ManualMode(WaterPump& waterPump, IObservable<ButtonState>& button, IObservable<TimerEvent>& timer);
    ~ManualMode();

    // IObservers
    void OnEvent(ButtonState event) override;
    void OnEvent(TimerEvent event) override;

    // IOperationMode
    void Run() override;
    void Activate() override;
    void Deactivate() override;

private:
    WaterPump& m_waterPump;
    uint8_t m_safetyCounter = 0;
};