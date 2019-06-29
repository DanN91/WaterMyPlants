/*
  Water My Plants

  ToDo: Description

  Author: Daniel Nistor, Copyright © 2019
*/

const bool DEBUG_MODE = false;
void DebugInit()
{
//  Serial.begin(9600);
//  Serial.print("Debugging Mode: ");
//  Serial.println(DEBUG_MODE ? "ON" : "OFF");
}

void Debug(const char* text)
{
//  if (DEBUG_MODE)
//    Serial.println(text);
}

const byte PUMP_PIN = 0; // 13, Arduino Uno
const byte BUTTON_PIN = 1; // 8, Arduino Uno

boolean isTest = true;
const uint32_t SECOND_MS = 1350;
const uint32_t MINUTE_MS = 60 * SECOND_MS;
const uint32_t HOUR_MS = (isTest) ? SECOND_MS : 60 * MINUTE_MS * SECOND_MS;
const uint32_t DAY_MS = (isTest) ? 5 * HOUR_MS : 24 * HOUR_MS;
const uint32_t TIME_TO_WATER_MS = (isTest) ? 3 * SECOND_MS : 2 * DAY_MS;

const uint32_t WATERING_TIME_MS = 5 * SECOND_MS;

boolean isUnattended = true;

static bool stateButtonShared = false;
static uint32_t previousMillis = millis();

bool GetButtonState(byte buttonPin)
{
  // read the current momentary switch state
  int reading = digitalRead(buttonPin);

  // the last time the output pin was toggled
  static int lastButtonState = LOW;
  static uint32_t lastDebounceTime = 0;
  // if the momentary switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  // the debounce time; increase if the output flickers
  const byte debounceDelay = 300;
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    static bool buttonState = LOW;
    // if the button state has changed and is not noise
    if (reading != buttonState)
    {   
      buttonState = reading;

      // only toggle the state if the new button state is HIGH
      if (buttonState == HIGH)
        stateButtonShared = !stateButtonShared;
    }
  }

  lastButtonState = reading;

  return stateButtonShared;
}

void ResetButtonState()
{
  stateButtonShared = LOW;
}

void ManualMode(byte buttonPin, byte pumpPin)
{
  // read button state
  static bool actualState = LOW;
  const bool newState = GetButtonState(buttonPin);

  // write new state to water pump
  if (newState != actualState)
  {
    Debug(actualState ? "Actual: ON" : "Actual: OFF");
    
    digitalWrite(pumpPin, newState);
    Debug(newState ? "Manual: Pump ON" : "Manual: Pump OFF");

    // store current state
    actualState = newState;

    // default to auto when pump is OFF
    isUnattended = (newState == LOW) ? true : false;
    if (isUnattended)
      previousMillis = millis();

    Debug(isUnattended ? "Control Mode: Automatic" : "Control Mode: Manual");
  }
}

void AutomaticMode(byte pumpPin)
{
  const uint32_t currentMillis = millis();
  if ((uint32_t)(currentMillis - previousMillis) >= TIME_TO_WATER_MS)
  {
    // pump ON
    digitalWrite(pumpPin, HIGH);
    Debug("Auto: Pump ON");
  
    const uint32_t wateringStartedMillis = millis();
    do
    {
        // make space for aborting automatic watering
        const bool doAbort = GetButtonState(BUTTON_PIN);
        if (doAbort)
        {
          // stop pump immediately, give control to user
          isUnattended = false;
          ResetButtonState();
          break;
        }
    } while ((uint32_t)(millis() - wateringStartedMillis) < WATERING_TIME_MS);

    // pump OFF
    digitalWrite(pumpPin, LOW);
    Debug("Auto: Pump OFF");
  
    // start counting from now on
    if (isUnattended)
    {
      Debug("Auto: Wait to water again...");
    }
    else
    {
      Debug("Auto: Switched to Manual mode");
    }

    previousMillis = millis();
  }
}

void setup()
{
  DebugInit();

  // water pump
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  // manual watering button
  pinMode(BUTTON_PIN, INPUT);

  Debug("Initialized");
}

void loop()
{ 
  ManualMode(BUTTON_PIN, PUMP_PIN);
  if (isUnattended)
    AutomaticMode(PUMP_PIN);
}
