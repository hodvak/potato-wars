#pragma once
#include "MapObject/MovingMapObject.h"
#include "PlayerColor.h"
#include "MapObject/Textures/RockTexture.h"
#include <optional>

class Rock : public MovingMapObject
{
public:
    static const float RADIUS;
    static const float WEIGHT;
    
    Rock(const MapVector &position, 
         const MapVector &speed,
         GameMap* map,
         const std::optional<PlayerColor> &color);
    
    void update(const sf::Time &deltaTime) override;
    
    bool collideDD1(MovingMapObject *other_object) override;
    
    bool collideDD2(Character *other_object) override;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    int m_life;
    std::optional<PlayerColor> m_color;
    RockTexture m_texture;
};