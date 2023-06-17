#pragma once

#include "MapObject/MovingMapObject.h"
#include "MapObject/Textures/BombObjectTexture.h"

/**
 * class that represents a BOMB object in the game (not the explosion but the
 * rolling BOMB)
 * the BOMB object will explode after 10 seconds
 */
class Bomb : public MovingMapObject
{
public:
    const static float RADIUS;
    const static float WEIGHT;
    const static sf::Time TIME_TO_EXPLODE;
    const static Explosion BOMB; // the explosion BOMB
    
    Bomb(const MapVector &pos,
         const GameMap &map,
         BombHandler &bomb_handler);

    void update(const sf::Time &deltaTime) override;

    bool collideDD1(MovingMapObject &other_object) override;

    bool collideDD2(Character &other_object) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    BombObjectTexture m_texture;
    sf::Time m_time;
};