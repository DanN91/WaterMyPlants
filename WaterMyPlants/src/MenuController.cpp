/*
    ...
*/

#include <MenuController.h>

#include <MenuCreator.h>
#include <OperationModeHandler.h>

namespace
{
    constexpr const uint8_t LINE_OFFSET = 2;
} // anonymous

MenuController::MenuController(NokiaDisplay& display, PushButton& modeChanger, PushButton& menuNavigation, PushButton& execution, OperationModeHandler& operationModeHandler)
    : IObserver(ButtonState::Released, modeChanger)
    , m_stringsManager(Language::English) // #DNN:ToDo:Make it a persistent setting and read it here
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

    static auto lastValue = m_cursor.Value();
    if (const auto currentValue = m_cursor.Value(); m_cursor && currentValue != lastValue) // prepare item only when cursor changes
    {
        PrepareItemHandling();
        lastValue = currentValue;
    }
}

void MenuController::ChangeMenu(MenuCode menuCode)
{
    m_changeSetting.Reset(nullptr);
    m_menu = MenuCreator::Create(menuCode);

    // update range
    m_cursor.Range({ 0, (m_menu.ItemsCount() > 0) ? m_menu.ItemsCount() - 1 : 0 });
    PrepareItemHandling();
    WriteMenu(m_menu);
    m_cursor.Refresh(true);
}

void MenuController::WriteMenu(Menu& menu) const
{
    m_display.Clear();

    // title & separator
    m_display.Write(0, m_stringsManager.Read(m_menu.Title()), NokiaDisplay::Aligned::Left);
    m_display.SetCursor(1, 0);
    m_display.Write(m_stringsManager.Read(Strings::Address::TitleSeparator));

    // items: text + value
    for (uint8_t i = 0; i < m_menu.ItemsCount(); ++i)
        WriteMenuItem(i);
}

void MenuController::WriteMenuItem(uint8_t itemIndex) const
{
    if (const auto menuItem = m_menu.GetMenuItem(itemIndex))
    {
        const uint8_t itemLineIndex = LINE_OFFSET + itemIndex;
        m_display.Write(itemLineIndex, m_stringsManager.Read(menuItem->Text()), NokiaDisplay::Aligned::Left);
        m_display.Write(itemLineIndex, SettingsManager::Read(menuItem->Value()), NokiaDisplay::Aligned::Right);
    }
}

MenuCode MenuController::GetMenuByOperationMode(uint8_t operationModeIndex) const
{
    return static_cast<MenuCode>(operationModeIndex);
}

void MenuController::PrepareItemHandling()
{
    if (!m_cursor)
        return;

    if (const auto currentItem = m_menu.GetMenuItem(m_cursor.Value()))
        m_changeSetting.Reset(new ChangeSetting(m_display, m_menu, m_cursor.Value(), m_execution));
}