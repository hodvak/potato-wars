#include "Weapon/Creators/StoneThrowCreator.h"
#include "resources_manager.h"
#include "PlayerColor.h"
#include "Weapon/ThrowWeapon.h"
#include "MapObject/Rock.h"
#include <memory>

StoneThrowCreator::StoneThrowCreator(int amount,
                                     GameHelperData &gameHelperData) :
        WeaponCreator(amount, gameHelperData)
{

}

StoneThrowCreator::StoneThrowCreator(const StoneThrowCreator &other) :
        WeaponCreator(other.getAmount(), other.getGameHelperData())
{

}

const sf::Texture &StoneThrowCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(resources_manager::IMG_ROCK_PATH);
}

sf::IntRect StoneThrowCreator::getTextureRect() const
{
    return {
            (int)resources_manager::IMG_ROCK_SIZE.x * PlayerColor::SIZE,
            0,
            (int)resources_manager::IMG_ROCK_SIZE.x,
            (int)resources_manager::IMG_ROCK_SIZE.y
    };
}

std::unique_ptr<Weapon>
StoneThrowCreator::createWeaponImpl(Character &character)
{

    Rock * rock  = new Rock(
            character.getPosition(),
            {0, 0},
            character.getColor(),
            getGameHelperData());

    return std::make_unique<ThrowWeapon>(character,
                                         std::unique_ptr<Rock>(rock),
                                         getGameHelperData());
}

