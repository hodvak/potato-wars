#include "Weapon/Creators/ShotgunWeaponCreator.h"
#include "Weapon/Shotgun.h"
#include "resources_manager.h"
#include "PlayerColor.h"


ShotgunWeaponCreator::ShotgunWeaponCreator(const ShotgunWeaponCreator &other) :
        WeaponCreator(other.getAmount()),
        m_map(other.m_map),
        m_bombHandler(other.m_bombHandler)
{

}

ShotgunWeaponCreator::ShotgunWeaponCreator(int amount,
                                       const std::function<void(
                                               std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                                       const GameMap &map,
                                       BombHandler &bombHandler) :
        WeaponCreator(amount),
        m_map(map),
        m_addMapObjectFunc(addMapObjectFunc),
        m_bombHandler(bombHandler)
{

}

std::unique_ptr<Weapon>
ShotgunWeaponCreator::createWeaponImpl(const Character &character)
{
    return std::make_unique<Shotgun>(character, 
                                   m_addMapObjectFunc,
                                   m_map,
                                   m_bombHandler);
}

const sf::Texture &ShotgunWeaponCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(resources_manager::IMG_SHOTGUN_PATH);
}

sf::IntRect ShotgunWeaponCreator::getTextureRect() const
{
    sf::IntRect rect;
    rect.width = resources_manager::IMG_SHOTGUN_SIZE.x;
    rect.height = resources_manager::IMG_SHOTGUN_SIZE.y;
    rect.left = rect.width * (PlayerColor::SIZE);
    rect.top = 0;
    return rect;
}

std::unique_ptr<WeaponCreator> ShotgunWeaponCreator::copy() const
{
    return std::make_unique<ShotgunWeaponCreator>(*this);
}


