/*
  Water My Plants

  ToDo: Description

  Author: Daniel Nistor, Copyright © 2019
*/

const byte PUMP_PIN = 0;
const byte BUTTON_PIN = 1;

boolean isTest = true;

const long long HOUR_IN_MS = (isTest) ? 1000 : 60 * 60 * 1000;
const long long DAY_IN_MS = (isTest) ? 5 * HOUR_IN_MS : 24 * HOUR_IN_MS;

const long long WATER_TIME_MS = (isTest) ? DAY_IN_MS : 2 * DAY_IN_MS;

void ManualMode(byte buttonPin, byte pumpPin)
{
  static bool pumpState = LOW;
  static bool buttonState = HIGH;
  static int lastButtonState = LOW;
  
  // read the current momentary switch state
  int reading = digitalRead(buttonPin);

  // the last time the output pin was toggled
  unsigned long lastDebounceTime = 0;
  // if the momentary switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  // the debounce time; increase if the output flickers
  const unsigned long debounceDelay = 50;
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // if the button state has changed and is not noise
    if (reading != buttonState)
    {
      buttonState = reading;

      // only toggle the state if the new button state is HIGH
      if (buttonState == HIGH)
      {
        pumpState = !pumpState;
      }
    }
  }

  // toggle water pump
  digitalWrite(pumpPin, pumpState);

  lastButtonState = reading;
}

void AutomaticMode(byte pumpPin)
{
  // test only
  digitalWrite(pumpPin, LOW);
  delay(1000);
  digitalWrite(pumpPin, HIGH);
  delay(1000);
  //
}

void setup()
{
  // water pump
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  // manual watering button
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  ManualMode(BUTTON_PIN, PUMP_PIN);
  //AutomaticMode(PUMP_PIN);
}
