#include <Arduino.h>

#include <TogglePushButton.h>

class TestObserver final : public IPushButtonObserver
{
public:
  // IPushButtonObserver
  void WasPressed() override {}
};

TestObserver testObs;
TogglePushButton button(0, testObs);

void setup()
{
  // initialize hardware components
  button.Initialize();
}

void loop()
{
  // event-driven
}