#pragma once

#include <SFML/Graphics.hpp>
#include "SoundPlayer.h"
#include "GameHelperData.h"
/***
 * a class that represent the camera for the players turns
 * and controls the view of the game with the mouse
 */
class TeamCamera
{
public:
    TeamCamera(GameHelperData &gameHelperData);
    void reset();
    void update(const sf::Time &deltaTime);
    void handleMouseMoved(const sf::Vector2<int> &mousePosition);
    void handleScroll(float delta);

    [[nodiscard]] const sf::View &getView() const;

private:
    GameHelperData &m_gameHelperData;
    sf::FloatRect m_originalViewRect;
    float m_zoomLevel = 0;
    sf::View m_view;
    sf::Vector2<int> m_mousePosition;
    sf::Vector2<int> m_screenSize;

};