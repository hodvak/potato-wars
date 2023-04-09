#include "moving_map_object.h"
#include <iostream>

const double PI = 3.141592653589793;

MovingMapObject::MovingMapObject(float weight,
                                 sf::Vector2f pos,
                                 float radius,
                                 sf::Vector2f speed,
                                 sf::Vector2f forces)
        : m_weight(weight),
          m_forces(forces),
          m_velocity(speed),
          m_pos(pos),
          m_radius(radius),
          m_energy(0.5 * m_weight * sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y) - m_weight * GRAVITY * pos.y) // pos.y going down
{
}

void MovingMapObject::draw(sf::RenderTarget &target,
                           sf::Rect<float> cameraRect) const
{
    sf::Vector2f cameraOffset = {cameraRect.left, cameraRect.top};
    sf::Vector2f cameraRatio = {cameraRect.width / target.getSize().x,
                                cameraRect.height / target.getSize().y};

    sf::CircleShape shape;
    shape.setRadius(m_radius * cameraRatio.x);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((m_pos.x - cameraOffset.x) * cameraRatio.x,
                      (m_pos.y - cameraOffset.y) * cameraRatio.y);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);
    target.draw(shape);
}

void MovingMapObject::update_forces(const sf::Image &map,
                                    std::vector<std::unique_ptr<MovingMapObject>> &objects)
{
    sf::Vector2f total_normal_force = {0, 0};
    float total_fraction_force = 0;
    sf::Vector2f gravity_force = {0, GRAVITY * m_weight};
    float velocity_direction = atan2(m_velocity.y, m_velocity.x);

    for (int i = -m_radius; i < m_radius; i++)
    {
        for (int j = -m_radius; j < m_radius; j++)
        {
            if (i * i + j * j < m_radius * m_radius && (i != 0 || j != 0))
            {
                sf::Vector2f pos = {m_pos.x + i, m_pos.y + j};
                if (map.getPixel(pos.x, pos.y) == sf::Color::White)
                {
                    float normal_length =
                            sqrt(gravity_force.x * gravity_force.x +
                                 gravity_force.y * gravity_force.y) *
                            cos(atan2(j, i) -
                                atan2(gravity_force.y, gravity_force.x));
                    sf::Vector2f normal_force = {normal_length * (float) sin(
                            atan2(j, i) -
                            atan2(gravity_force.y, gravity_force.x)),
                                                 -normal_length * (float) cos(
                                                         atan2(j, i) -
                                                         atan2(gravity_force.y,
                                                               gravity_force.x))};
                    normal_force *= 3.0f;

                    sf::Vector2f fraction_force = {-normal_force.y,
                                                   normal_force.x};

                    float fraction_length_in_direction =
                            sqrt(fraction_force.x * fraction_force.x +
                                 fraction_force.y * fraction_force.y) *
                            cos(atan2(fraction_force.y, fraction_force.x) -
                                velocity_direction);
                    if (fraction_length_in_direction < 0)
                    {
                        fraction_length_in_direction *= -1;
                    }

                    total_normal_force += normal_force;
                    total_fraction_force += fraction_length_in_direction;
                }
            }
        }
    }
    m_forces = gravity_force + total_normal_force;

    float force_in_fraction_direction =
            total_fraction_force * cos(velocity_direction);
    if (total_fraction_force * STATIC_FRICTION < force_in_fraction_direction)
    {
        m_forces += {-total_fraction_force * DYNAMIC_FRICTION *
                     (float) sin(velocity_direction),
                     -total_fraction_force * DYNAMIC_FRICTION *
                     (float) cos(velocity_direction)};
    }
    else
    {
        m_forces += {
                -force_in_fraction_direction * (float) sin(velocity_direction),
                -force_in_fraction_direction * (float) cos(velocity_direction)};
    }

//    if(force_in_fraction_direction < 0)
//    {
//        force_in_fraction_direction *= -1;
//    }
//    if(force_in_fraction_direction >= force_in_fraction_direction * STATIC_FRICTION)
//    {
//        m_forces += {-total_fraction_force * (float) sin(velocity_direction),
//                     -total_fraction_force * (float) cos(velocity_direction)};
//    }
//    else
//    {
//        m_forces += {-DYNAMIC_FRICTION * (float) sin(velocity_direction),
//                     -DYNAMIC_FRICTION * (float) cos(velocity_direction)};
//    }

//    total_fraction_force *= -DYNAMIC_FRICTION;
//    m_forces += {total_fraction_force * (float) cos(velocity_direction),
//                 total_fraction_force * (float) sin(velocity_direction)};
//    

}

void MovingMapObject::update_speed(float time)
{
    m_velocity += m_forces * time / m_weight;
    float new_energy = 0.5 * m_weight * sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y) - m_weight * GRAVITY * m_pos.y;
    
    if(new_energy > m_energy)
    {
        m_velocity *= 2*(m_energy + m_weight * GRAVITY * m_pos.y)/m_weight/sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    }
    m_energy = 0.5 * m_weight * sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y) - m_weight * GRAVITY * m_pos.y;;
    std::cout << m_velocity.x << " " << m_velocity.y << std::endl;
}

void MovingMapObject::update_location(float time)
{
    m_pos += m_velocity * time + m_forces * time * time / (2 * m_weight);

}