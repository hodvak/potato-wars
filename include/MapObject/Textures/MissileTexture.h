#pragma once
#include <optional>
#include <SFML/Graphics.hpp>
#include "PlayerColor.h"

class MissileTexture : public sf::Drawable
{
public:
    MissileTexture(std::optional<PlayerColor> color, float angle, float radius);
    
    void update(const sf::Time &deltaTime);
    
    void setAngle(float angle);

    ~MissileTexture() override = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    
    

private:
    const sf::Time TIME_FOR_ANIMATION = sf::seconds(0.05f);
    
    float m_radius;
    std::optional<PlayerColor> m_color;
    float m_angle;
    sf::Time m_time;
    std::vector<sf::Vector2f> m_cloudPositions;
};