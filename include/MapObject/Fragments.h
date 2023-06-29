#pragma once
#include "MovingMapObject.h"
#include <functional>
class Fragments : public MovingMapObject
{
public:
    Fragments(const MapVector &pos,GameHelperData &gameHelperData,
              const MapVector &velocity);
    void update(const sf::Time &deltaTime) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    bool collideDD1(MovingMapObject &otherObject) override;

private:
    int m_numOfBounces;
    float m_rotation;

};
