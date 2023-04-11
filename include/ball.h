#include "moving_map_object.h"

class Ball : public MovingMapObject
{
public:
    Ball(sf::Vector2f pos, sf::Image *map);
    float collision_map() override;
    void update(float deltaTime, sf::Image &map) override;
    bool collide(MovingMapObject *otherObject) override;
    bool collide_dd(Ball *otherObject) override;
    void on_death() override;
private:
    int m_numOfBounces;
};