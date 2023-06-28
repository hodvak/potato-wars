#include "Weapon/Creators/BazookaCreator.h"
#include "Weapon/Bazooka.h"
#include "resources_manager.h"

BazookaCreator::BazookaCreator(int amount, GameHelperData &gameHelperData)
        : WeaponCreator(amount, gameHelperData)
{

}

BazookaCreator::BazookaCreator(BazookaCreator &other):
        WeaponCreator(other.getAmount(), other.getGameHelperData())
{

}

std::unique_ptr<Weapon> BazookaCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<Bazooka>(
            character,
            getGameHelperData());
}

const sf::Texture &BazookaCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(resources_manager::IMG_BAZOOKA_PATH);
}

sf::IntRect BazookaCreator::getTextureRect() const
{
    return {
            (int)resources_manager::IMG_BAZOOKA_SIZE.x * PlayerColor::SIZE,
            0,
            (int)resources_manager::IMG_BAZOOKA_SIZE.x,
            (int)resources_manager::IMG_BAZOOKA_SIZE.y
    };
}
