#pragma once
#include "MapObject/MovingMapObject.h"
#include "PlayerColor.h"
#include "MapObject/Textures/RockTexture.h"
#include <optional>

/**
 * a Rock is a rock in the game
 * a rock can be neutral or belong to a player
 * a rock can hit a character and decrease its life for 3 
 */
class Rock : public MovingMapObject
{
public:
    /**
     * the radius of the rock
     */
    static const float RADIUS;
    
    /**
     * the weight of the rock
     */
    static const float WEIGHT;
    
    
    Rock(const MapVector &position,
         const MapVector &speed,
         const std::optional<PlayerColor> &color,
         GameHelperData &gameHelperData);
    
    void update(const sf::Time &deltaTime) override;
    
    bool collideDD1(MovingMapObject &other_object) override;
    
    bool collideDD2(Character &otherObject) override;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    int m_life;
    std::optional<PlayerColor> m_color;
    RockTexture m_texture;
};