#include "Weapon/Creators/RifleWeaponCreator.h"
#include "Weapon/Rifle.h"
#include "resources_manager.h"
#include "PlayerColor.h"


RifleWeaponCreator::RifleWeaponCreator(int amount,
                                       GameMap *map,
                                       const std::function<void(
                                               std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                                       BombHandler &bombHandler) :
        WeaponCreator(amount),
        m_map(map),
        m_addMapObjectFunc(addMapObjectFunc),
        m_bombHandler(bombHandler)
{

}

std::unique_ptr<Weapon>
RifleWeaponCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<Rifle>(character, m_addMapObjectFunc, *m_map,
                                   m_bombHandler);
}

const sf::Texture *RifleWeaponCreator::getTexture() const
{
    return resources_manager::getTexture(
            "resources/Images/Textures/rifles.png");
}

sf::IntRect RifleWeaponCreator::getTextureRect() const
{
    return {0, 0, 100, 100};
}

std::unique_ptr<WeaponCreator> RifleWeaponCreator::copy() const
{
    return std::make_unique<RifleWeaponCreator>(*this);
}

RifleWeaponCreator::RifleWeaponCreator(const RifleWeaponCreator &other) :
        WeaponCreator(other.getAmount()), m_map(other.m_map),
        m_bombHandler(other.m_bombHandler)
{

}
