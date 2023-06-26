#include "Weapon/Creators/JumpCreator.h"
#include "Weapon/Jump.h"
#include "resources_manager.h"

JumpCreator::JumpCreator(int amount,
                         GameHelperData &gameHelperData) :
        WeaponCreator(amount, gameHelperData)
{

}

const sf::Texture &JumpCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(
            resources_manager::IMG_JUMP_PATH);
}

sf::IntRect JumpCreator::getTextureRect() const
{
    return {(int) resources_manager::IMG_JUMP_SIZE.x * PlayerColor::SIZE,
            0,
            (int) resources_manager::IMG_JUMP_SIZE.x,
            (int) resources_manager::IMG_JUMP_SIZE.y};
}


std::unique_ptr<Weapon>
JumpCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<Jump>(character, getGameHelperData());
}
