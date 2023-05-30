#include "ScreenManager.h"

ScreenManager::ScreenManager(std::unique_ptr<Screen> screen) :
        m_currentScreen(std::move(screen))
{

}

void ScreenManager::run(sf::RenderWindow &window)
{
    while (m_currentScreen)
    {
        m_currentScreen = m_currentScreen->run(window);
    }
}