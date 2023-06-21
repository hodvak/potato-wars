#pragma once

#include <SFML/Graphics.hpp>

class TeamCamera
{
public:
    TeamCamera(float width, float height);
    void reset();
    void update(const sf::Time &deltaTime);
    void handleMouseMoved(const sf::Vector2<int> &mousePosition);
    void handleScroll(int delta);

    [[nodiscard]] const sf::View &getView() const;

private:
    const sf::FloatRect m_originalViewRect;
    float m_zoomLevel = 0;
    sf::View m_view;
    sf::Vector2<int> m_mousePosition;
    sf::Vector2<int> m_screenSize;

};