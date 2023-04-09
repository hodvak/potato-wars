#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

const float GRAVITY = 35;
const float STATIC_FRICTION = 1;
const float DYNAMIC_FRICTION = 0.5;

class MovingMapObject
{
public:
    MovingMapObject(float weight,
                    sf::Vector2f pos,
                    float radius,
                    sf::Vector2f speed = {0, 0},
                    sf::Vector2f power = {0, 0});

    void draw(sf::RenderTarget &target, sf::Rect<float> cameraRect) const;

    void update_forces(const sf::Image &map,
                             std::vector<std::unique_ptr<MovingMapObject>> &objects);

    void update_speed(float time);

    void update_location(float time);


    virtual ~MovingMapObject() = default;

private:
    float m_weight;
    sf::Vector2f m_forces;
    sf::Vector2f m_velocity;
    sf::Vector2f m_pos;
    float m_radius;
    float m_energy;
};