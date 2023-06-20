#include "Weapon/Creators/StoneThrowCreator.h"
#include "resources_manager.h"
#include "PlayerColor.h"
#include "Weapon/ThrowWeapon.h"
#include "MapObject/Rock.h"
#include <memory>

StoneThrowCreator::StoneThrowCreator(int amount,
                                     const std::function<void(
                                             std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                                     const GameMap &map,
                                     BombHandler &bombHandler)
        :
        WeaponCreator(amount),
        m_map(map),
        m_addMapObjectFunc(addMapObjectFunc),
        m_bombHandler(bombHandler)
{

}

StoneThrowCreator::StoneThrowCreator(const StoneThrowCreator &other) :
        WeaponCreator(other.getAmount()),
        m_map(other.m_map),
        m_bombHandler(other.m_bombHandler),
        m_addMapObjectFunc(other.m_addMapObjectFunc)
{

}

const sf::Texture *StoneThrowCreator::getTexture() const
{
    return resources_manager::getTexture(resources_manager::IMG_ROCK_PATH);
}

sf::IntRect StoneThrowCreator::getTextureRect() const
{
    return sf::IntRect(
            resources_manager::IMG_ROCK_SIZE.x * PlayerColor::SIZE,
            0,
            resources_manager::IMG_ROCK_SIZE.x,
            resources_manager::IMG_ROCK_SIZE.y
    );
}

std::unique_ptr<WeaponCreator> StoneThrowCreator::copy() const
{
    return std::make_unique<StoneThrowCreator>(*this);
}

std::unique_ptr<Weapon>
StoneThrowCreator::createWeaponImpl(Character &character)
{

    Rock * rock  = new Rock(
            character.getPosition(),
            {0, 0},
            character.getColor(),
            m_map,
            m_bombHandler
            );

    return std::make_unique<ThrowWeapon>(character,
                                         std::unique_ptr<Rock>(rock),
                                         m_addMapObjectFunc);
}

const GameMap &StoneThrowCreator::getMap() const
{
    return m_map;
}
