#include "Weapon/Creators/JumpCreator.h"
#include "Weapon/Jump.h"
#include "resources_manager.h"
JumpCreator::JumpCreator(int amount,const std::function<void(std::unique_ptr<MovingMapObject> &&)>
&addMapObjectFunc) : WeaponCreator(amount), m_addMapObjectFunc(addMapObjectFunc)
{

}

const sf::Texture &JumpCreator::getTexture() const
{
    return resources_manager::get<sf::Texture>(resources_manager::IMG_JUMP_PATH);
}

sf::IntRect JumpCreator::getTextureRect() const
{
    return sf::IntRect(resources_manager::IMG_JUMP_SIZE.x * PlayerColor::SIZE, 
                       0, 
                       resources_manager::IMG_JUMP_SIZE.x,
                       resources_manager::IMG_JUMP_SIZE.y);
}

std::unique_ptr<WeaponCreator> JumpCreator::copy() const
{
    return std::make_unique<JumpCreator>(this->getAmount(),m_addMapObjectFunc);
}

std::unique_ptr<Weapon>
JumpCreator::createWeaponImpl(Character &character)
{
    return std::make_unique<Jump>(character, m_addMapObjectFunc);
}
