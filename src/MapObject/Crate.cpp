#include <numbers>
#include "MapObject/Crate.h"
#include "resources_manager.h"
#include "Const.h"
#include "Physics.h"

Crate::Crate(MapVector pos, GameMap *map,
             std::unique_ptr<WeaponCreator> &&weapon_creator) :
        MovingMapObject(100, pos, map, 20),
        m_weapon_creator(std::move(weapon_creator))
{

}

void Crate::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    sf::Sprite sprite;
    sf::Sprite weaponSprite;;

    weaponSprite.setTexture(*m_weapon_creator->getTexture());
    weaponSprite.setScale(
            getRadius() * 2 / m_weapon_creator->getTextureRect().width,
            getRadius() * 2 / m_weapon_creator->getTextureRect().height);
    weaponSprite.setTextureRect(m_weapon_creator->getTextureRect());
    weaponSprite.setOrigin(m_weapon_creator->getTextureRect().width / 2,
                           m_weapon_creator->getTextureRect().height / 2);
    weaponSprite.setRotation(getRotation());
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
        weaponSprite.setPosition(0, -getRadius());

    }

    sprite.setScale(scale);

    sprite.setRotation(getRotation() * 180 / std::numbers::pi_v<float>);
    weaponSprite.setRotation(getRotation() * 180 / std::numbers::pi_v<float>);



    target.draw(sprite, states);
    target.draw(weaponSprite, states);


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




