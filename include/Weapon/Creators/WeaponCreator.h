#pragma once

#include <memory>
#include "Weapon/Weapon.h"
#include "GameMap.h"
#include "GameHelperData.h"

class Character;

class WeaponCreator
{
public:
    explicit WeaponCreator(int amount, GameHelperData &gameHelperData);
    std::unique_ptr<Weapon> createWeapon(Character &character);
    virtual ~WeaponCreator() = default;
    [[nodiscard]] int getAmount() const;
    void addAmount(int amount);
    [[nodiscard]] virtual const sf::Texture &getTexture() const = 0;
    [[nodiscard]] virtual sf::IntRect getTextureRect() const = 0;
    [[nodiscard]] GameHelperData &getGameHelperData() const;

protected:
    virtual std::unique_ptr<Weapon> createWeaponImpl(Character &character) = 0;
    
private:
    int m_amount;
    GameHelperData &m_gameHelperData;
};