#include "Weapon/Textures/ThrowWeaponTexture.h"

#include <numbers>

ThrowWeaponTexture::ThrowWeaponTexture(const Character &character,
                                       const MapVector &direction,
                                       float maxDistance):
m_character(character),
m_direction(direction),
m_maxDistance(maxDistance)
{
    

}

void ThrowWeaponTexture::update(const sf::Time &deltaTime)
{
    
}

void ThrowWeaponTexture::setDirection(const MapVector &direction)
{
    m_direction = direction;
}

void ThrowWeaponTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    float thickness = m_character.getRadius()/2.0f;
    // draw a line in diagonal of thickness radius/2
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(m_direction.getMagnitude(), thickness));
    shape.setOrigin(0,thickness/2.0f);
    shape.setRotation(m_direction.getAngle() * 180 / std::numbers::pi_v<float> + 180);
    
    // 255 is not a magic number, it's the max value of a color (0xFF)
    // the calculation here makes
    // the color smoothly change from red to green
    int redness = (int)(255 * m_direction.getMagnitude() / m_maxDistance);
    int greenness = 255 - redness;
    
    shape.setFillColor(sf::Color(redness, greenness, 0));
    
    shape.setPosition(m_character.getPosition());
    target.draw(shape, states);
}
