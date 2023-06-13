#pragma once
#include "MapObject/MovingMapObject.h"
#include "Weapon/Creators/WeaponCreator.h"

class Crate : public MovingMapObject
{
public:
    Crate(MapVector pos,GameMap *map,const sf::Texture *texture,sf::IntRect overShape);
    void update(const sf::Time &deltaTime) override;
    bool collideDD1(MovingMapObject *other_object) override;
    bool collideDD2(Character *other_object) override;
    bool collideDD2(Crate *other_object) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void updateVelocity(const sf::Time &deltaTime) override;
private:
    bool onGround = false;
    const sf::Texture *m_overTexture;
    sf::IntRect m_overShape;

};
