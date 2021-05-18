/*
    ...
*/

#include <MenuController.h>

#include <MenuCreator.h>
#include <OperationModeHandler.h>

MenuController::MenuController(NokiaDisplay& display, PushButton& modeChanger, PushButton& menuNavigation, PushButton& execution, OperationModeHandler& operationModeHandler)
    : IObserver(ButtonState::Released, modeChanger)
    , m_display(display)
    , m_operationHandler(operationModeHandler)
    , m_execution(execution)
    , m_changeSetting(nullptr)
    , m_cursor(display, menuNavigation, '>', 0)
    , m_menu(MenuCreator::Create(GetMenuByOperationMode(m_operationHandler.CurrentModeIndex())))
{
    modeChanger.Register(this);
}

void MenuController::Initialize()
{
    OnEvent(ButtonState::Released);
}

void MenuController::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
        ChangeMenu(GetMenuByOperationMode(m_operationHandler.CurrentModeIndex()));
}

void MenuController::Handle()
{
    m_cursor.Refresh();

    // prepare item
    static auto lastValue = m_cursor.Value();
    if (const auto currentValue = m_cursor.Value(); m_cursor && currentValue != lastValue)
    {
        PrepareItemHandling(currentValue);
        lastValue = currentValue;
    }
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
    for (uint8_t i = 0; i < m_menu.ItemsCount(); ++i)
    {
        const auto menuItem = m_menu.GetMenuItem(i);
        if (!menuItem)
            continue;

        m_display.Write(i + 2, m_stringsManager.Read(menuItem->Text()), NokiaDisplay::Aligned::Left);
        m_display.Write(i + 2, m_settingsManager.Read(menuItem->Value()), NokiaDisplay::Aligned::Right);
    }

    // update range
    m_cursor.Range({ 0, (m_menu.ItemsCount() > 0) ? m_menu.ItemsCount() - 1 : 0 });
    PrepareItemHandling(m_cursor.Value());
    m_cursor.Refresh(true);
}

MenuCode MenuController::GetMenuByOperationMode(uint8_t operationModeIndex) const
{
    return static_cast<MenuCode>(operationModeIndex);
}

void MenuController::PrepareItemHandling(uint8_t itemIndex)
{
    if (const auto currentItem = m_menu.GetMenuItem(itemIndex); currentItem)
        m_changeSetting.Reset(new ChangeSetting(m_settingsManager, *currentItem, m_execution));
}