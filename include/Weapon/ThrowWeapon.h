#pragma once

#include <optional>
#include <functional>
#include <memory>

#include "Weapon/Weapon.h"
#include "Weapon/Textures/ThrowWeaponTexture.h"
#include "MapObject/MovingMapObject.h"

class ThrowWeapon : public Weapon
{
public:
    ThrowWeapon(const Character &character,
                std::unique_ptr<MovingMapObject> &&weapon,
                const std::function<void(std::unique_ptr<MovingMapObject> &&)>
                &addMapObjectFunc
    );

    void handleMouseMoved(const MapVector &mousePosition) override;

    void handleMousePressed(const MapVector &mousePosition) override;

    void update(const sf::Time &deltaTime) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:

    void fixPosition();

    const Character &m_character;
    const float m_maxDistance = 100;
    std::unique_ptr<MovingMapObject> m_weapon;
    MapVector m_startVelocity;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
    ThrowWeaponTexture m_texture;
};