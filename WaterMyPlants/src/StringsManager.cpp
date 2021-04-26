/*
    StringsManager: wrapper over EEPROM which aids in writing and reading strings from EEPROM.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "StringsManager.h"

#include <EEPROM.h>

StringsManager::StringsManager(Language language)
    : m_language(language)
{
}

void StringsManager::WriteAllStrings()
{
    using namespace Strings;

	// set all sector to null-terminator
	for (uint16_t i = STRINGS_BEGIN; i < STRINGS_END; ++i)
		EEPROM.write(i, 0);

    // ENU
    {
        Write(Address::TitleSeparator, SEPARATOR);

        // Operation Modes
        Write(Address::ManualModeTitle, ENU::MANUAL_MODE_TITLE);
        Write(Address::TimerModeTitle, ENU::TIMER_MODE_TITLE);
        Write(Address::SensorModeTitle, ENU::SENSOR_MODE_TITLE);

        // Timer Mode
        Write(Address::TimerModeDuration, ENU::TIMER_MODE_CALIBRATION_DURATION);
        Write(Address::TimerModeFrequency, ENU::TIMER_MODE_CALIBRATION_FREQUENCY);

        // Sensor Mode
        Write(Address::SensorModeDry, ENU::SENSOR_MODE_DRY);
        Write(Address::SensorModeWet, ENU::SENSOR_MODE_WET);
    }

    // ROM
    {
        // #TODO
    }
}

String StringsManager::Get(Strings::Address stringAddress) const
{
    using namespace Strings;

	String text;
	text.reserve(25);

    auto addressValue = static_cast<uint16_t>(stringAddress);
	for (auto i = addressValue; i < STRINGS_END; ++i)
	{
		char characterRead = EEPROM.read(i);
		if (characterRead == 0 || characterRead == 255)
			break;

		text.concat(characterRead);
	}

	return text;
}

void StringsManager::Write(Strings::Address address, const char* text)
{
    using namespace Strings;

    const uint8_t length = strlen(text) + 1; // + NULL-terminator
    uint16_t addressValue = static_cast<uint16_t>(address);
    if (!text || (addressValue + length > STRINGS_END))
        return;

    for (uint8_t i = 0; i < length && addressValue < EEPROM.length(); i++)
        EEPROM[addressValue++] = text[i];
}