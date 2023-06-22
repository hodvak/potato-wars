#include "Weapon/Creators/MinigunWeaponCreator.h"
#include "Weapon/Shotgun.h"
#include "resources_manager.h"
#include "PlayerColor.h"
#include "Weapon/Minigun.h"


MinigunWeaponCreator::MinigunWeaponCreator(int amount,
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
MinigunWeaponCreator::createWeaponImpl(const Character &character)
{
    return std::make_unique<Minigun>(character, 
                                   m_addMapObjectFunc,
                                   m_map,
                                   m_bombHandler);
}

const sf::Texture *MinigunWeaponCreator::getTexture() const
{
    return resources_manager::getTexture(resources_manager::IMG_MINIGUN_PATH);
}

sf::IntRect MinigunWeaponCreator::getTextureRect() const
{
    sf::IntRect rect;
    rect.width = resources_manager::IMG_MINIGUN_SIZE.x;
    rect.height = resources_manager::IMG_MINIGUN_SIZE.y;
    rect.left = rect.width * (PlayerColor::SIZE);
    rect.top = 0;
    return rect;
}

std::unique_ptr<WeaponCreator> MinigunWeaponCreator::copy() const
{
    return std::make_unique<MinigunWeaponCreator>(*this);
}

MinigunWeaponCreator::MinigunWeaponCreator(const MinigunWeaponCreator &other) :
        WeaponCreator(other.getAmount()), m_map(other.m_map),
        m_bombHandler(other.m_bombHandler)
{

}
