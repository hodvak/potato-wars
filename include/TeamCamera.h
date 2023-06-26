#pragma once

#include <SFML/Graphics.hpp>
#include "GameHelperData.h"

class TeamCamera
{
public:
    TeamCamera(sf::FloatRect mapRect,
               sf::Vector2f originalViewSize,
               GameHelperData &gameHelperData);
    
    void reset();
    void update(const sf::Time &deltaTime);
    void handleMouseMoved(const sf::Vector2<int> &mousePosition);
    void handleScroll(float delta);

    [[nodiscard]] sf::View getView() const;

private:
    constexpr static const float MAX_ZOOM = 6;
    constexpr static const float MIN_ZOOM = 0;
    constexpr static const float ZOOM_SPEED = 0.5f;
    
    
    void fixBorders();
    
    const sf::FloatRect m_mapRect;
    const sf::Vector2f m_originalViewSize;
    sf::FloatRect m_viewRect;
    GameHelperData &m_gameHelperData;
    float m_zoomLevel;
    sf::Vector2f m_position;
};