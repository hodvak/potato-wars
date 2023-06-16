#pragma once

#include <optional>
#include <SFML/Graphics.hpp>
#include "PlayerColor.h"

/**
 * a class for the rock object texture
 */
class RockTexture: public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param color the color of the rock or nullopt if it is a neutral rock
     */
    explicit RockTexture(const std::optional<PlayerColor> &color = std::nullopt);
    
    /**
     * set the life level of the rock [0,2]
     * @param life the life level of the rock
     */
    void setLife(int life);
    
    /**
     * draw the rock object
     * @param target where to draw to
     * @param states the states to draw with (and specifically the position)
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * set the angle of the rock
     * @param angle the angle of the rock (in radians)
     */
    void setAngle(float angle);

private:
    /**
     * the color of the rock or nullopt if it is a neutral rock
     */
    std::optional<PlayerColor> m_color;
    
    /**
     * the life that the rock has
     */
    int m_life;
    
    /**
     * the angle of the rock (in degrees)
     */
    float m_rotation;
};