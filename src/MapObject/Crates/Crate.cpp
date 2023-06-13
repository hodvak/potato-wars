#include <numbers>
#include "MapObject/Crates/Crate.h"
#include "resources_manager.h"

#include "Physics.h"


Crate::Crate(MapVector pos, GameMap *map,const sf::Texture *texture,
             sf::IntRect overShape) :
        MovingMapObject(100, pos, map, 10),
        m_overTexture(texture),
        m_overShape(overShape)
{

}

void Crate::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    sf::Sprite sprite;
    sf::Sprite overTexture;

    overTexture.setTexture(*m_overTexture);
    overTexture.setScale(
            getRadius() * 2 / m_overShape.width,
            getRadius() * 2 / m_overShape.height);
    overTexture.setTextureRect(m_overShape);
    overTexture.setOrigin(m_overShape.width / 2,
                          m_overShape.height / 2);
    overTexture.setRotation(getRotation());
    const sf::Texture *texture = resources_manager::getTexture(
            "resources/images/Textures/CrateTextureNP.png");
    sf::Vector2f scale = {
            getRadius() * 2 / texture->getSize().x,
            getRadius() * 2 / texture->getSize().y
    };


    if (onGround || isRest())
    {
        sprite.setTexture(*resources_manager::getTexture(
                "resources/images/Textures/CrateTextureNP.png"));
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2,
                         sprite.getTexture()->getSize().y / 2);


    }
    else
    {

        sprite.setTexture(*resources_manager::getTexture(
                "resources/images/Textures/CrateTexture.png"));
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2,
                         sprite.getTexture()->getSize().y - getRadius());
        overTexture.setPosition(0, -getRadius());

    }

    sprite.setScale(scale);

    sprite.setRotation(getRotation() * 180 / std::numbers::pi_v<float>);
    overTexture.setRotation(getRotation() * 180 / std::numbers::pi_v<float>);


    target.draw(sprite, states);
    target.draw(overTexture, states);


}

bool Crate::collideDD1(MovingMapObject *other_object)
{


    return other_object->collideDD2(this);

}

void Crate::update(const sf::Time &deltaTime)
{

    if (!isRest())
    {
        updateForces(deltaTime);
        updateVelocity(deltaTime);
        updatePosition(deltaTime);
        std::optional<float> rot = collisionMap();
        if (rot)
        {
            setVelocity({0, 0});
            stop();
            onGround = true;
            setRotation(*rot - std::numbers::pi_v<float> / 2);
        }

    }
}

void Crate::updateVelocity(const sf::Time &deltaTime)
{
    setVelocity({0, 80});
}

bool Crate::collideDD2(Character *other_object)
{
    kill();
    return true;
}

bool Crate::collideDD2(Crate *other_object)
{
    return true;
}




