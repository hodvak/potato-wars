#include "moving_map_object.h"
#include "Map.h"

class Ball : public MovingMapObject
{
public:
    Ball(sf::Vector2f pos, Map *map, BombHandler *bombHandler);
    float collision_map() override;
    void update(float deltaTime) override;
    bool collide(MovingMapObject *otherObject) override;
    bool collide_dd(Ball *otherObject) override;
    void on_death() override;
private:
    int m_numOfBounces;
};