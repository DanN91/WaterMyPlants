/*
    ...
*/

#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include <PushButton.h>

#include <Menu.h>
#include <MenuCursor.h>
#include <MenuCreator.h>

#include <UniquePtr.h>
#include <ChangeSetting.h>

#include <SettingsManager.h>
#include <StringsManager.h>

#include <OperationModeHandler.h>

class NokiaDisplay;

class MenuController final : public IObserver<ButtonState>
{
public:
    MenuController(NokiaDisplay& display, PushButton& modeChanger, PushButton& menuNavigation, PushButton& execution, OperationModeHandler& operationModeHandler);
    ~MenuController() = default;

    void Initialize();

    // IObserver
    void OnEvent(ButtonState event);

    void Handle();
    bool IsEmptyMenu() const { return m_menu.ItemsCount() == 0; }// #DNN:CALIBRATION ONLY

private:
    void ChangeMenu(MenuCode menuCode);
    void WriteMenu(Menu& menu) const;
    void WriteMenuItem(uint8_t itemIndex) const;
    MenuCode GetMenuByOperationMode(uint8_t operationMode) const;

    void PrepareItemHandling();

    StringsManager m_stringsManager;
    NokiaDisplay& m_display;
    OperationModeHandler& m_operationHandler;

    PushButton& m_execution;
    UniquePtr<ChangeSetting> m_changeSetting;

    MenuCursor m_cursor;
    Menu m_menu;
};