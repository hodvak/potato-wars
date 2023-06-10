#pragma once

#include <SFML/Graphics.hpp>

class BombObjectTexture : public sf::Drawable
{
public:
    explicit BombObjectTexture(float radius,const sf::Time &time);
    void setReminingTime(const sf::Time& time);
    void setAngle(float angle);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    

private:
    float m_angle;
    float m_radius;
    sf::Time m_remainedTime;

};