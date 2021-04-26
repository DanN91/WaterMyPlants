

#include "ChangeSetting.h"

#include <NokiaDisplay.h>
#include <MenuItem.h>
#include <SettingsManager.h>
#include <StringsManager.h>
#include <PushButton.h>

ChangeSetting::ChangeSetting(NokiaDisplay& display, MenuItem& item, SettingsManager& settings, StringsManager& strings, PushButton& button)
    : m_display(display)
    , m_item(item)
    , m_settings(settings)
    , m_strings(strings)
    , m_button(button)
{
}

void ChangeSetting::Execute()
{
    m_display.Write(5, 1234, NokiaDisplay::Aligned::Center);
}
