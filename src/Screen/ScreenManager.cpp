#include "Screen/ScreenManager.h"

ScreenManager::ScreenManager(std::unique_ptr<Screen> &&screen) :
        m_currentScreen(std::move(screen))
{

}

void ScreenManager::run(sf::RenderWindow &window)
{
    while (m_currentScreen)
    {
        // empty the event queue
        sf::Event event{};
        while (window.pollEvent(event))
        {
        }
        m_currentScreen = m_currentScreen->run(window);
    }
}