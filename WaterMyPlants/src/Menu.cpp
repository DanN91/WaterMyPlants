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
