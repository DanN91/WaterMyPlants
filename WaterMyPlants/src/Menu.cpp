/*
    ...
*/

#include "Menu.h"

void Menu::Title(const Strings::Address& titleAddress)
{
	m_titleAddress = titleAddress;
}

Strings::Address Menu::Title() const
{
	return m_titleAddress;
}

bool Menu::AddMenuItem(const MenuItem& item)
{
    return m_items.Add(item);
}

const MenuItem* Menu::GetMenuItem(uint8_t index) const
{
    return m_items[index];
}

uint8_t Menu::ItemsCount() const
{
	return m_items.Count();
}

// void Menu::Execute(byte itemIndex, eButtonState buttonState) const
// {
// 	if (itemIndex < m_itemsCount)
// 	{
// 		HandleSettingChange(itemIndex);
// 	}
// }

// void Menu::HandleSettingChange(byte lineIndex)
// {
// 	// get position on the display
// 	const byte columnIndex = (StringManager::Get(m_itemsAddrs[lineIndex]).length() + 1) * 7;
// 	switch (m_menuCode)
// 	{
// 		case MenuCode::Temperature:
// 		{
// 			switch (lineIndex)
// 			{
// 				case 0: // Desired
// 				{
// 					ChangeSetting desiredChange(SettingsAddresses::DesiredTemperature);
// 					desiredChange.Execute(lineIndex, columnIndex);
// 					break;
// 				}
// 				case 1: // Trigger
// 				{
// 					ChangeSetting triggerChange(SettingsAddresses::TemperatureTrigger);
// 					triggerChange.Execute(lineIndex, columnIndex);
// 					break;
// 				}
// 			}
// 			break;
// 		}

// 		case MenuCode::Humidity:
// 		{
// 			switch (lineIndex)
// 			{
// 				case 0: // Desired
// 				{
// 					ChangeSetting desiredChange(SettingsAddresses::DesiredHumidity);
// 					desiredChange.Execute(lineIndex, columnIndex);
// 					break;
// 				}
// 				case 1: // Trigger
// 				{
// 					ChangeSetting triggerChange(SettingsAddresses::HumidityTrigger);
// 					triggerChange.Execute(lineIndex, columnIndex);
// 					break;
// 				}
// 			}
// 			break;
// 		}

// 		case MenuCode::Settings:
// 		{
// 			switch (lineIndex)
// 			{
// 				// Time
// 				case 0:
// 				{
// 					ChangeSetting timeChange(SettingsAddresses::Time);
// 					timeChange.Execute(lineIndex, columnIndex);
// 					break;
// 				}

// 				// Date
// 				case 1:
// 				{
// 					ChangeSetting dateChange(SettingsAddresses::Date);
// 					dateChange.Execute(lineIndex, columnIndex);
// 					break;
// 				}

// 				// FactoryReset
// 				case 2:
// 				{
// 					SettingsManager::Get().FactoryReset();
// 					break;
// 				}
// 			}
// 			break;
// 		}

// 		case MenuCode::Statistics:
// 		{
// 			switch (lineIndex)
// 			{
// 				case 0: // Toggle On/Off
// 				{
// 					ChangeSetting toggleChange(SettingsAddresses::LogStatistics);
// 					toggleChange.Execute(lineIndex, columnIndex);
// 					break;
// 				}

// 				case 1: // Logging Time Interval
// 				{
// 					// From Until
// 					ChangeSetting fromChange(SettingsAddresses::LogStatisticsFromHour);
// 					fromChange.Execute(lineIndex + 1, 14);

// 					ChangeSetting untilChange(SettingsAddresses::LogStatisticsUntilHour);
// 					untilChange.Execute(lineIndex + 1, 45);
// 					break;
// 				}
// 			}
// 			break;
// 		}

// 		default:
// 			// nothing
// 			break;
// 	}
// }
