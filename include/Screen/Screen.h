#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
struct Settings
{
    bool m_mute;
    float m_volume;
};

/**
 * Abstract class for screens
 * all the screens can be run and return the next screen, or nullptr if  there
 * is no next screen
 * 
 * abstract so no `Screen.cpp` file is needed
 */
class Screen
{
public:
    /**
     * run the screen
     * @param window the window to draw on
     * @return the next screen, or nullptr if there is no next screen
     */
    virtual std::unique_ptr<Screen> run(sf::RenderWindow &window) = 0;
    
    /**
     * virtual destructor (due to the fact that this is an abstract class)
     */
    virtual ~Screen() = default;
    [[nodiscard]] const Settings &getSettings() const;
    void setSettings(const Settings &settings);
private:
    Settings m_settings = {false, 100};
};
