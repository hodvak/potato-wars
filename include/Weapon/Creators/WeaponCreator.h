#pragma once

#include <memory>
#include "Weapon/Weapon.h"
#include "MapObject/Character.h"
#include "GameMap.h"


class WeaponCreator
{
public:
    explicit WeaponCreator(int amount);
    std::unique_ptr<Weapon> createWeapon(Character &character);
    [[nodiscard]] int getAmount() const;
    void addAmount(int amount);
    [[nodiscard]] virtual const sf::Texture *getTexture() const = 0;
    [[nodiscard]] virtual sf::IntRect getTextureRect() const = 0;

protected:
    virtual std::unique_ptr<Weapon> createWeaponImpl(Character &character) = 0;
    
private:
    int m_amount;
};