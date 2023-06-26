#include "Weapon/Creators/ShotgunWeaponCreator.h"
#include "Weapon/Shotgun.h"
#include "resources_manager.h"
#include "PlayerColor.h"


ShotgunWeaponCreator::ShotgunWeaponCreator(const ShotgunWeaponCreator &other) :
        WeaponCreator(other.getAmount(), other.getGameHelperData())
{

}

ShotgunWeaponCreator::ShotgunWeaponCreator(int amount,
                                           GameHelperData &gameHelperData):
        WeaponCreator(amount,gameHelperData)
{

}

std::unique_ptr<Weapon>
ShotgunWeaponCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<Shotgun>(character, 
                                     getGameHelperData());
}

const sf::Texture &ShotgunWeaponCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(resources_manager::IMG_SHOTGUN_PATH);
}

sf::IntRect ShotgunWeaponCreator::getTextureRect() const
{
    sf::IntRect rect;
    rect.width = (int)resources_manager::IMG_SHOTGUN_SIZE.x;
    rect.height = (int)resources_manager::IMG_SHOTGUN_SIZE.y;
    rect.left = rect.width * (PlayerColor::SIZE);
    rect.top = 0;
    return rect;
}

