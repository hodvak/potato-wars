#include "Weapon/Creators/RifleWeaponCreator.h"
#include "Weapon/Rifle.h"
#include "resources_manager.h"
#include "PlayerColor.h"


RifleWeaponCreator::RifleWeaponCreator(int amount,
                                       GameHelperData &gameHelperData) :
        WeaponCreator(amount, gameHelperData)
{

}

std::unique_ptr<Weapon>
RifleWeaponCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<Rifle>(character, 
                                   getGameHelperData());
}

const sf::Texture &RifleWeaponCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(resources_manager::IMG_RIFLE_PATH);
}

sf::IntRect RifleWeaponCreator::getTextureRect() const
{
    sf::IntRect rect;
    rect.width = (int)resources_manager::IMG_RIFLE_SIZE.x;
    rect.height = (int)resources_manager::IMG_RIFLE_SIZE.y;
    rect.left = rect.width * (PlayerColor::SIZE);
    rect.top = 0;
    return rect;
}


RifleWeaponCreator::RifleWeaponCreator(const RifleWeaponCreator &other) :
        WeaponCreator(other.getAmount(),other.getGameHelperData())
{

}
