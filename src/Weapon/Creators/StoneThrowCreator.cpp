#include "Weapon/Creators/StoneThrowCreator.h"
#include "resources_manager.h"
#include "PlayerColor.h"
#include "Weapon/ThrowWeapon.h"
#include "MapObject/Rock.h"
#include <memory>

StoneThrowCreator::StoneThrowCreator(int amount, GameMap *map,
                                     const std::function<void(
                                             std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc)
        :
        WeaponCreator(amount),
        m_map(map),
        m_addMapObjectFunc(addMapObjectFunc)
{

}

StoneThrowCreator::StoneThrowCreator(const StoneThrowCreator &other) :
        WeaponCreator(other.getAmount()), m_map(other.m_map)
{

}

const sf::Texture *StoneThrowCreator::getTexture() const
{
    return resources_manager::getTexture(
            "resources/Images/Textures/rocks.png");
}

sf::IntRect StoneThrowCreator::getTextureRect() const
{
    return {0, 0, 100, 100};
}

std::unique_ptr<WeaponCreator> StoneThrowCreator::copy() const
{
    return std::make_unique<StoneThrowCreator>(*this);
}

std::unique_ptr<Weapon>
StoneThrowCreator::createWeaponImpl(Character &character)
{

    std::unique_ptr<Rock> rock ( new Rock(
            character.getPosition(),
            {0, 0},
            m_map,
            character.getColor()));


    return std::make_unique<ThrowWeapon>(character, std::move(rock),
                                         m_addMapObjectFunc);

}

GameMap *StoneThrowCreator::getMap() const
{
    return m_map;
}
