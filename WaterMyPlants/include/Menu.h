// #DNN:TODO

#pragma once

#include <Arduino.h>

#include <Array.h>
#include <MenuItem.h>
#include <IOperationMode.h>
#include <PersistenceManager.h>

class Menu final
{
public:
    Menu() = default;
    ~Menu() = default;

    void Title(const Strings::Address& titleAddress);
    Strings::Address Title() const;

    bool AddMenuItem(const MenuItem& item);
    const MenuItem* GetMenuItem(uint8_t index) const;

    uint8_t ItemsCount() const;

    // void Execute(uint8_t itemIndex, eButtonState buttonState) const;

private:
    // void HandleSettingChange(uint8_t lineIndex);

    static constexpr uint8_t MAX_ITEMS_COUNT = 4;
    Array<MenuItem, MAX_ITEMS_COUNT> m_items;

    Strings::Address m_titleAddress = Strings::Address::Invalid;
};
