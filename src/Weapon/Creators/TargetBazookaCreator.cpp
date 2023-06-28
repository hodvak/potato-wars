#include "Weapon/Creators/TargetBazookaCreator.h"
#include "Weapon/Bazooka.h"
#include "resources_manager.h"
#include "Weapon/TargetBazooka.h"

TargetBazookaCreator::TargetBazookaCreator(int amount, GameHelperData &gameHelperData)
        : WeaponCreator(amount, gameHelperData)
{

}

TargetBazookaCreator::TargetBazookaCreator(TargetBazookaCreator &other):
        WeaponCreator(other.getAmount(), other.getGameHelperData())
{

}

std::unique_ptr<Weapon> TargetBazookaCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<TargetBazooka>(
            character,
            getGameHelperData());
}

const sf::Texture &TargetBazookaCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(resources_manager::IMG_TARGET_BAZOOKA_PATH);
}

sf::IntRect TargetBazookaCreator::getTextureRect() const
{
    return {
            (int)resources_manager::IMG_TARGET_BAZOOKA_SIZE.x * PlayerColor::SIZE,
            0,
            (int)resources_manager::IMG_TARGET_BAZOOKA_SIZE.x,
            (int)resources_manager::IMG_TARGET_BAZOOKA_SIZE.y
    };
}
