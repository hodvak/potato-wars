#pragma once
#include "Weapon/Creators/WeaponCreator.h"

class TargetBazookaCreator : public WeaponCreator
{
public:
    TargetBazookaCreator(int amount,
                   GameHelperData &gameHelperData);


    TargetBazookaCreator(TargetBazookaCreator &other);
    
    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;
    
    const sf::Texture &getTexture() const override;
    
    sf::IntRect getTextureRect() const override;

private:

};