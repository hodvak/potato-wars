#include "Weapon/Creators/RifleWeaponCreator.h"
#include "Weapon/Rifle.h"
#include "resources_manager.h"
#include "PlayerColor.h"


RifleWeaponCreator::RifleWeaponCreator(int amount,
                                       const std::function<void(
                                               std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                                       const GameMap &map,
                                       BombHandler &bombHandler) :
        WeaponCreator(amount),
        m_map(map),
        m_addMapObjectFunc(addMapObjectFunc),
        bombHandler(bombHandler)
{

}

std::unique_ptr<Weapon>
RifleWeaponCreator::createWeaponImpl(const Character &character)
{
    return std::make_unique<Rifle>(character, 
                                   m_addMapObjectFunc,
                                   m_map,
                                   bombHandler);
}

const sf::Texture *RifleWeaponCreator::getTexture() const
{
    return resources_manager::getTexture(resources_manager::IMG_RIFLE_PATH);
}

sf::IntRect RifleWeaponCreator::getTextureRect() const
{
    sf::IntRect rect;
    rect.width = resources_manager::IMG_RIFLE_SIZE.x;
    rect.height = resources_manager::IMG_RIFLE_SIZE.y;
    // for now, its color YELLOW,
    // todo: add to texture natural color (to the png)
    rect.left = rect.width * (PlayerColor::YELLOW);
    rect.top = 0;
    return rect;
}
