#include "Weapon/Creators/BombThrowCreator.h"
#include "Weapon/ThrowWeapon.h"
#include "resources_manager.h"

BombThrowCreator::BombThrowCreator(int amount, GameHelperData &gameHelperData)
        :
        WeaponCreator(amount, gameHelperData)
{

}

BombThrowCreator::BombThrowCreator(const BombThrowCreator &other) :
        WeaponCreator(other.getAmount(), other.getGameHelperData())
{

}

std::unique_ptr<Weapon>
BombThrowCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<ThrowWeapon>(character,
                                         std::make_unique<Bomb>(
                                                 character.getPosition(),
                                                 getGameHelperData()
                                         ),
                                         getGameHelperData());
}

const sf::Texture &BombThrowCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(
            resources_manager::IMG_BOMB_PATH);
}

sf::IntRect BombThrowCreator::getTextureRect() const
{
    const sf::Texture &texture = getTexture();
    return {0, 0, (int)texture.getSize().x, (int)texture.getSize().y};
}

