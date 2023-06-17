#include "Weapon/Creators/JumpCreator.h"
#include "Weapon/Jump.h"
#include "resources_manager.h"
JumpCreator::JumpCreator(int amount,const std::function<void(std::unique_ptr<MovingMapObject> &&)>
&addMapObjectFunc) : WeaponCreator(amount), m_addMapObjectFunc(addMapObjectFunc)
{

}

const sf::Texture *JumpCreator::getTexture() const
{
    return resources_manager::getTexture("resources/images/Textures/jump.png");
}

sf::IntRect JumpCreator::getTextureRect() const
{
    return {0,0,542,243};
}

std::unique_ptr<WeaponCreator> JumpCreator::copy() const
{
    return std::unique_ptr<WeaponCreator>(std::make_unique<JumpCreator>(this->getAmount(),m_addMapObjectFunc));
}

std::unique_ptr<Weapon>
JumpCreator::createWeaponImpl(const Character &character)
{
    return std::make_unique<Jump>(const_cast<Character &>(character), m_addMapObjectFunc);
}
