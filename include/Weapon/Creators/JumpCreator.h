#pragma once
#include "WeaponCreator.h"
#include "MapObject/MovingMapObject.h"
#include <functional>
class JumpCreator : public WeaponCreator
{
public:
    explicit JumpCreator(int amount,const std::function<void(std::unique_ptr<MovingMapObject> &&)>
    &addMapObjectFunc);

    [[nodiscard]] const sf::Texture *getTexture() const override;
    [[nodiscard]] sf::IntRect getTextureRect() const override;
    std::unique_ptr<WeaponCreator> copy() const override;
private:
    std::unique_ptr<Weapon> createWeaponImpl(const Character &character) override;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
};