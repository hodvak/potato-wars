#pragma once
#include "PlayerColor.h"
#include <SFML/Graphics.hpp>
#include <optional>

class RockTexture: public sf::Drawable
{
public:
    explicit RockTexture(const std::optional<PlayerColor> &color = std::nullopt);
    void setLife(int life);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setAngle(float angle);

private:
    std::optional<PlayerColor> m_color;
    int m_life;
    float m_rotation;
};