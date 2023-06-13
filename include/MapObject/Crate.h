#pragma once
#include "MovingMapObject.h"
#include "Weapon/Creators/WeaponCreator.h"

class Crate : public MovingMapObject
{
public:
    Crate(MapVector pos, GameMap *map, std::unique_ptr<WeaponCreator> &&weapon_creator);

    void update(const sf::Time &deltaTime) override;
    bool collideDD1(MovingMapObject *other_object) override;
    bool collideDD2(Character *other_object) override;
    bool collideDD2(Crate *other_object) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void updateVelocity(const sf::Time &deltaTime) override;
private:
    bool onGround = false;
    std::unique_ptr<WeaponCreator> m_weapon_creator;
};
