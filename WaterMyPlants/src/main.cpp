#include <Arduino.h>

#include <Hardware.h>
#include <PushButton.h>

#include <OperationModeHandler.h>

PushButton modeChangerButton(Hardware::MODE_CHANGER_BUTTON_PIN, 1);
OperationModeHandler operationHandler(OperationMode::Manual, modeChangerButton);

void setup()
{
    Serial.begin(9600);

    // initialize hardware components
    modeChangerButton.Initialize();
    operationHandler.Initialize();

    Serial.println("Initialized.");
}

void loop()
{
    modeChangerButton.HandleEvents();
    operationHandler.Run();
}