#include "Screen/Screen.h"
const Settings &Screen::getSettings() const
{
    return m_settings;
}

void Screen::setSettings(const Settings &settings)
{
    m_settings = settings;
}
