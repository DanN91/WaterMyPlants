/*
    ...
*/

#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include <PushButtonMasks.h>

#include <Menu.h>
#include <MenuCursor.h>
#include <MenuCreator.h>

#include <SettingsManager.h>
#include <StringsManager.h>

#include <OperationModeHandler.h>

class NokiaDisplay;

class MenuController final : public IObserver<ButtonState>
{
public:
    MenuController(NokiaDisplay& display, PushButton& modeChanger, PushButton& menuNavigation, OperationModeHandler& operationModeHandler);
    ~MenuController() = default;

    void Initialize();

    // IObserver
    void OnEvent(ButtonState event);

    void Handle();

private:
    void ChangeMenu(MenuCode menuCode);
    MenuCode GetMenuByOperationMode(OperationMode operationMode) const;

    SettingsManager m_settingsManager;
    StringsManager m_stringsManager;
    NokiaDisplay& m_display;
    OperationModeHandler& m_operationHandler;
    MenuCursor m_cursor;
    Menu m_menu;
};