#include <Arduino.h>

#include <Hardware.h>
#include <PushButton.h>
#include <NokiaDisplay.h>

#include <OperationModeHandler.h>

PushButton modeChangerButton(Hardware::MODE_CHANGER_BUTTON_PIN, 1);
OperationModeHandler operationHandler(OperationMode::Manual, modeChangerButton);

NokiaDisplay& display = NokiaDisplay::getInstance(6, 5, 4, 3, 2);

void setup()
{
    Serial.begin(9600);

    // initialize hardware components
    modeChangerButton.Initialize();
    operationHandler.Initialize();

    display.initialize();
    display.write("Initialized.");
}

void loop()
{
    modeChangerButton.HandleEvents();
    operationHandler.Run();
}