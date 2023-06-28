#include "MapObject/Fragments.h"
#include "resources_manager.h"
#include <numbers>

Fragments::Fragments(const MapVector &pos, GameHelperData &gameHelperData,
                     const MapVector &velocity) :
        MovingMapObject(pos, 10, 100, gameHelperData, velocity),
        m_numOfBounces(3)
{

}

void Fragments::update(const sf::Time &deltaTime)
{
    if (!isRest() && m_numOfBounces > 0)
    {
        updateForces(deltaTime);
        updateVelocity(deltaTime);
        updatePosition(deltaTime);
        updateRotation(deltaTime);
        if (collisionMap())
        {
            m_numOfBounces--;
        }
        return;
    }
    kill();
}

bool Fragments::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}

void Fragments::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    const sf::Texture texture = resources_manager::get<sf::Texture>(
            resources_manager::IMG_FRAGMENTS_PATH);
    sf::Sprite sprite(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setScale(10.f/texture.getSize().x, 10.f/texture.getSize().y);
    sprite.setRotation(MovingMapObject::getRotation() * 180 / std::numbers::pi);
    sprite.setPosition(getPosition());
    target.draw(sprite, states);

}
