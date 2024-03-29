#pragma once

#include <functional>
#include <memory>
#include "MapObject/Character.h"
#include "Weapon/Weapon.h"
#include "Weapon/Textures/GunTexture.h"


class Gun : public Weapon
{
public:
    Gun(const Character &owner,
        const std::string &texturePath,
        const sf::Vector2u &rectTextureSize,
        GameHelperData &gameHelperData);


    void handleMouseMoved(const MapVector &mousePosition) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(const sf::Time &deltaTime) override;

protected:
    void shot(const MapVector &power,
              float damage,
              float weight,
              float radius);

private:
    GunTexture m_texture;
    const Character &m_character;
};