/*
    PersistenceManager: wrapper over EEPROM which aids in writing and reading data from EEPROM.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "PersistenceManager.h"

#include <EEPROM.h>

void PersistenceManager::WriteAllStrings()
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

void PersistenceManager::WriteDefaultSettings()
{
    TimerModeDuration(60); // 60 seconds
    TimerModeFrequency(1); // every 1 day
    LastOperationMode(0); // Manual mode
    SensorModeDry(20); // 20 %
    SensorModeWet(70); // 70 %
}

String PersistenceManager::Get(Strings::Address stringAddress) const
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

uint32_t PersistenceManager::Get(Settings::Address settingAddress) const
{
    using namespace Settings;

    switch (settingAddress)
    {
        case Address::TimerModeDuration: return TimerModeDuration();
        case Address::TimerModeFrequency: return TimerModeFrequency();
        case Address::SensorModeDry: return SensorModeDry();
        case Address::SensorModeWet: return SensorModeWet();

        default: return 9999;
    }
}

uint16_t PersistenceManager::TimerModeDuration() const
{
    uint16_t durationInSeconds = 0;
    EEPROM.get<uint16_t>(static_cast<uint16_t>(Settings::Address::TimerModeDuration), durationInSeconds);

    return durationInSeconds;
}

void PersistenceManager::TimerModeDuration(uint16_t seconds)
{
    EEPROM.put<uint16_t>(static_cast<uint16_t>(Settings::Address::TimerModeDuration), seconds);
}

uint8_t PersistenceManager::TimerModeFrequency() const
{
    uint8_t frequencyInDays = 0;
    EEPROM.get<uint8_t>(static_cast<uint16_t>(Settings::Address::TimerModeFrequency), frequencyInDays);

    return frequencyInDays;
}

void PersistenceManager::TimerModeFrequency(uint8_t days)
{
    EEPROM.put<uint8_t>(static_cast<uint16_t>(Settings::Address::TimerModeFrequency), days);
}

uint8_t PersistenceManager::SensorModeDry() const
{
    return ReadByte(Settings::Address::SensorModeDry);
}

void PersistenceManager::SensorModeDry(uint8_t percent)
{
    EEPROM.write(static_cast<uint16_t>(Settings::Address::SensorModeDry), percent);
}

uint8_t PersistenceManager::SensorModeWet() const
{
    return ReadByte(Settings::Address::SensorModeWet);
}

void PersistenceManager::SensorModeWet(uint8_t percent)
{
    EEPROM.write(static_cast<uint16_t>(Settings::Address::SensorModeWet), percent);
}

uint8_t PersistenceManager::LastOperationMode() const
{
    return ReadByte(Settings::Address::LastOperationMode);
}

void PersistenceManager::LastOperationMode(uint8_t modeIndex)
{
    WriteByte(Settings::Address::LastOperationMode, modeIndex);
}

void PersistenceManager::Write(Strings::Address address, const char* text)
{
    using namespace Strings;

    const uint8_t length = strlen(text) + 1; // + NULL-terminator
    uint16_t addressValue = static_cast<uint16_t>(address);
    if (!text || (addressValue + length > STRINGS_END))
        return;

    for (uint8_t i = 0; i < length && addressValue < EEPROM.length(); i++)
        EEPROM[addressValue++] = text[i];
}

void PersistenceManager::WriteByte(Settings::Address address, uint8_t value)
{
    const auto addressValue = static_cast<uint16_t>(address);
    if (addressValue < Settings::SETTINGS_BEGIN || addressValue >= Settings::SETTINGS_END)
        return;

    EEPROM[addressValue] = value;
}

uint8_t PersistenceManager::ReadByte(Settings::Address address) const
{
    return EEPROM.read(static_cast<uint16_t>(Settings::Address::LastOperationMode));
}