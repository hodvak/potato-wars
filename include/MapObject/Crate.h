#pragma once
#include "MovingMapObject.h"

class Crate : public MovingMapObject
{
public:
    Crate(MapVector pos, GameMap *map);
    std::optional<float> collisionMap() override;
    void update(const sf::Time &deltaTime) override;
    bool collideDD1(MovingMapObject *other_object) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void updateVelocity(const sf::Time &deltaTime) override;
private:
    bool onGround = false;
};
