#pragma once
#include "Weapon/Creators/WeaponCreator.h"

class BazookaCreator : public WeaponCreator
{
public:
    BazookaCreator(int amount,
                   GameHelperData &gameHelperData);


    BazookaCreator(BazookaCreator &other);
    
    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;
    
    const sf::Texture &getTexture() const override;
    
    sf::IntRect getTextureRect() const override;

private:

};