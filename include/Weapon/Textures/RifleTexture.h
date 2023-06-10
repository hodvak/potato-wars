#pragma once

#include "MapVector.h"
#include "PlayerColor.h"

class RifleTexture : public sf::Drawable
{
public:
    RifleTexture(PlayerColor color, 
                 MapVector position, 
                 MapVector aimPosition, 
                 float radius);
    
    void setPosition(MapVector position);
    void setAimPosition(MapVector aimPosition);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    PlayerColor m_color;
    MapVector m_position;
    MapVector m_aimPosition;
    float m_radius;
};