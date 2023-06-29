#include <numbers>

#include "Weapon/Textures/ThrowWeaponTexture.h"
#include "resources_manager.h"

ThrowWeaponTexture::ThrowWeaponTexture(const Character &character,
                                       const MapVector &direction,
                                       const MovingMapObject &weapon,
                                       float maxDistance) :
        m_character(character),
        m_direction(direction),
        m_maxDistance(maxDistance),
        m_weapon(weapon)
{


}

void ThrowWeaponTexture::update(const sf::Time &deltaTime)
{

}

void ThrowWeaponTexture::setDirection(const MapVector &direction)
{
    m_direction = direction;
}

void ThrowWeaponTexture::draw(sf::RenderTarget &target,
                              sf::RenderStates states) const
{
    float thickness = m_character.getRadius() / 2.0f;
    // draw a line in diagonal of thickness radius/2
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(m_direction.getMagnitude(), thickness));
    shape.setOrigin(0, thickness / 2.0f);
    shape.setRotation(
            m_direction.getAngle() * 180 / std::numbers::pi_v<float> + 180);

    // 255 is not a magic number, it's the max value of a color (0xFF)
    // the calculation here makes
    // the color smoothly change from red to green
    int redness = (int) (255 * m_direction.getMagnitude() / m_maxDistance);
    int greenness = 255 - redness;

    shape.setFillColor(sf::Color(redness, greenness, 0));

    shape.setPosition(m_character.getPosition());
    target.draw(shape, states);
    
    sf::Sprite slingshot;
    slingshot.setTexture(resources_manager::get<sf::Texture>(
            resources_manager::IMG_SLINGSHOT_PATH));
    
    slingshot.scale((m_character.getRadius() * 2 * 2) /
                    slingshot.getTexture()->getSize().x,
                    (m_character.getRadius() * 2 * 2) /
                    slingshot.getTexture()->getSize().y);

    slingshot.setOrigin(slingshot.getTexture()->getSize().x / 2.0f,
                        slingshot.getTexture()->getSize().y / 2.0f);

    if (m_direction.getAngle() > std::numbers::pi_v<float> / 2.0f ||
        m_direction.getAngle() < -std::numbers::pi_v<float> / 2.0f)
    {
        slingshot.scale(1, -1);
    }
    slingshot.setPosition(m_character.getPosition());
    slingshot.setRotation(
            m_direction.getAngle() * 180 / std::numbers::pi_v<float>);
    target.draw(slingshot, states);

    states.transform.translate(-m_direction);
    target.draw(m_weapon, states);

}
