/*
    ...
*/

#pragma once

#include <IObservable.h>
#include "PushButtonMasks.h"

class PushButton final : public IObservable
{
public:
    PushButton(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT);

    void Initialize() const;

    void HandleEvents();

private:
    const uint8_t m_pin;
};