

#pragma once

#include <Arduino.h>

#include <PersistenceManager.h>

class MenuItem final
{
public:
    MenuItem(Strings::Address stringAddress, Settings::Address settingAddress)
        : m_stringAddress(stringAddress)
        , m_settingAddress(settingAddress)
    {
    }

    MenuItem() = default;
    ~MenuItem() = default;

    // copyable and movable
    MenuItem(const MenuItem&) = default;
    MenuItem& operator=(const MenuItem&) = default;

    MenuItem(MenuItem&&) = default;
    MenuItem& operator=(MenuItem&&) = default;

    Strings::Address Text() const
    {
        return m_stringAddress;
    }

    Settings::Address Value() const
    {
        return m_settingAddress;
    }

private:
    Strings::Address m_stringAddress = Strings::Address::Invalid;
    Settings::Address m_settingAddress = Settings::Address::Invalid;
};
