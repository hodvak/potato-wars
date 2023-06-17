#include "Weapon/Creators/BombThrowCreator.h"
#include "Weapon/ThrowWeapon.h"
#include "resources_manager.h"
BombThrowCreator::BombThrowCreator(int amount, const std::function<void(
        std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                                   const GameMap &map, BombHandler &bombHandler):
        WeaponCreator(amount),
        m_map(map),
        m_bombHandler(bombHandler),
        m_addMapObjectFunc(addMapObjectFunc)
{

}

BombThrowCreator::BombThrowCreator(const BombThrowCreator &other):
        WeaponCreator(other.getAmount()),
        m_map(other.m_map),
        m_bombHandler(other.m_bombHandler),
        m_addMapObjectFunc(other.m_addMapObjectFunc)
{

}

std::unique_ptr<Weapon>
BombThrowCreator::createWeaponImpl(const Character &character)
{
    return std::unique_ptr<Weapon>(std::make_unique<ThrowWeapon>(character,
                                                                 std::make_unique<Bomb>(
                                                                            character.getPosition(),
                                                                            m_map,
                                                                            m_bombHandler
                                                                         ),
                                                                         m_addMapObjectFunc));
}

const sf::Texture *BombThrowCreator::getTexture() const
{
    return resources_manager::getTexture(resources_manager::IMG_BOMB_PATH);
}

sf::IntRect BombThrowCreator::getTextureRect() const
{
    return {0,0,100,100};
}

std::unique_ptr<WeaponCreator> BombThrowCreator::copy() const
{
    return std::unique_ptr<WeaponCreator>(std::make_unique<BombThrowCreator>(*this));
}
