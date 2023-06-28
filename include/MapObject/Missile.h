#pragma once

#include "MapObject/MovingMapObject.h"
#include "MapObject/Textures/MissileTexture.h"
#include "PlayerColor.h"


class Missile : public MovingMapObject
{
public:
    static const float RADIUS;
    
    Missile(const MapVector &position,
            GameHelperData &data,
            float angle,
            PlayerColor color);

    void update(const sf::Time &deltaTime) override;
    
    void setAngle(float angle);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    bool collideDD1(MovingMapObject &otherObject) override;

    bool collideDD2(Character &otherObject) override;

    ~Missile() override = default;

private:
    MissileTexture m_texture;
    sf::Time m_time;
    static const float SPEED;
    static const float MASS;
    static const Explosion EXPLOSION;

};