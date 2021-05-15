/*
    ...
*/

#include <MenuController.h>

#include <MenuCreator.h>
#include <OperationModeHandler.h>

MenuController::MenuController(NokiaDisplay& display, PushButton& modeChanger, PushButton& menuNavigation, OperationModeHandler& operationModeHandler)
    : IObserver(ButtonState::Released, modeChanger)
    , m_display(display)
    , m_operationHandler(operationModeHandler)
    , m_cursor(display, menuNavigation, '>', 0)
    , m_menu(MenuCreator::Create(GetMenuByOperationMode(m_operationHandler.CurrentMode())))
{
}

void MenuController::Initialize()
{
    OnEvent(ButtonState::Released);
}

void MenuController::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
        ChangeMenu(GetMenuByOperationMode(m_operationHandler.CurrentMode()));
}

void MenuController::Handle()
{
    m_cursor.Refresh();
}

void MenuController::ChangeMenu(MenuCode menuCode)
{
    m_menu = MenuCreator::Create(menuCode);

    m_display.Clear();

    // title & separator
    m_display.Write(0, m_stringsManager.Read(m_menu.Title()), NokiaDisplay::Aligned::Center);
    m_display.SetCursor(1, 0);
    m_display.Write(m_stringsManager.Read(Strings::Address::TitleSeparator));

    // items: text + value
    for (auto i = 0; i < m_menu.ItemsCount(); ++i)
    {
        const auto menuItem = m_menu.GetMenuItem(i);
        if (!menuItem)
            continue;

        m_display.Write(i + 2, m_stringsManager.Read(menuItem->Text()), NokiaDisplay::Aligned::Left);
        m_display.Write(i + 2, m_settingsManager.Read(menuItem->Value()), NokiaDisplay::Aligned::Right);
    }

    // update range
    m_cursor.Range({ 0, (m_menu.ItemsCount() > 0) ? m_menu.ItemsCount() - 1 : 0 });
    m_cursor.Refresh(true);
}

MenuCode MenuController::GetMenuByOperationMode(OperationMode operationMode) const
{
    switch (operationMode)
    {
        case OperationMode::Manual:
            return MenuCode::Manual;

        case OperationMode::Timer:
            return MenuCode::Timer;

        case OperationMode::Sensor:
            return MenuCode::Sensor;
    }

    return MenuCode::None;
}