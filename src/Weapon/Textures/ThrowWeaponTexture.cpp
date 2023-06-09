#include <numbers>
#include "Weapon/Textures/ThrowWeaponTexture.h"


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
    // draw a line in diagonal of thickness 5
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(m_direction.getMagnitude(), 5));
    shape.setOrigin(0,2.5);
    shape.setRotation(m_direction.getAngle() * 180 / std::numbers::pi + 180);
    
    int redness = 255 * m_direction.getMagnitude() / m_maxDistance;
    int greenness = 255 - redness;
    
    shape.setFillColor(sf::Color(redness, greenness, 0));
    
    shape.setPosition(m_character.getPosition());
    target.draw(shape, states);
}
