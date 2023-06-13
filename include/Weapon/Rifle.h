#pragma once
#include <functional>
#include <memory>
#include "MapObject/Character.h"
#include "Weapon/Weapon.h"
#include "Weapon/Textures/RifleTexture.h"

class Rifle : public Weapon
{
public:
    Rifle(Character &owner, 
          const std::function<void(std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
          GameMap &map,
          BombHandler &bombHandler);

    void handleMouseMoved(const MapVector &mousePosition) override;
    void handleMousePressed(const MapVector &mousePosition) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(const sf::Time &deltaTime) override;
    
private:
    MapVector m_aimPosition;
    Character &m_character;
    RifleTexture m_texture;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
    GameMap &m_map;
    BombHandler &m_bombHandler;
};