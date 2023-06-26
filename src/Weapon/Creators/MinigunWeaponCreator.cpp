#include "Weapon/Creators/MinigunWeaponCreator.h"
#include "Weapon/Shotgun.h"
#include "resources_manager.h"
#include "PlayerColor.h"
#include "Weapon/Minigun.h"


MinigunWeaponCreator::MinigunWeaponCreator(int amount,
                                           GameHelperData &gameHelperData) :
        WeaponCreator(amount, gameHelperData)
{

}

std::unique_ptr<Weapon>
MinigunWeaponCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<Minigun>(character, 
                                     getGameHelperData());
}

const sf::Texture &MinigunWeaponCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(resources_manager::IMG_MINIGUN_PATH);
}

sf::IntRect MinigunWeaponCreator::getTextureRect() const
{
    sf::IntRect rect;
    rect.width = (int)resources_manager::IMG_MINIGUN_SIZE.x;
    rect.height = (int)resources_manager::IMG_MINIGUN_SIZE.y;
    rect.left = rect.width * (PlayerColor::SIZE);
    rect.top = 0;
    return rect;
}

MinigunWeaponCreator::MinigunWeaponCreator(const MinigunWeaponCreator &other) :
        WeaponCreator(other.getAmount(), other.getGameHelperData())
{

}
