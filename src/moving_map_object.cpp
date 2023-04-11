#include "moving_map_object.h"
#include <cmath>
#include <iostream>

const double PI = 3.141592653589793;

MovingMapObject::MovingMapObject(float weight,
                                 sf::Vector2f pos,
                                 sf::Image *map,
                                 float radius,
                                 sf::Vector2f startVelocity,
                                 BombHandler *bombHandler)
        : m_weight(weight),
          m_velocity(startVelocity),
          m_pos(pos),
          m_radius(radius),
          m_forces(0, m_weight * GRAVITY),
          m_resting(false),
          m_alive(true),
          m_map(map),
          m_bombHandler(bombHandler)
{
}

void MovingMapObject::draw(sf::RenderTarget &target,
                           const sf::Rect<float> &cameraRect) const
{
    sf::Vector2f cameraOffset = {cameraRect.left, cameraRect.top};
    sf::Vector2f cameraRatio = {(float) target.getSize().x / cameraRect.width,
                                (float) target.getSize().y / cameraRect.height};

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

void MovingMapObject::update_velocity(float deltaTime)
{
    m_velocity += m_forces / m_weight * deltaTime;
}

void MovingMapObject::update_forces(float deltaTime)
{
    m_forces = {0, m_weight * GRAVITY};
}

void MovingMapObject::update_position(float deltaTime)
{
    m_pos += m_velocity * deltaTime;
}

void MovingMapObject::update(float deltaTime, sf::Image &map)
{
    if (!m_resting)
    {
        update_forces(deltaTime);
        update_velocity(deltaTime);
        update_position(deltaTime);
        collision_map();
    }
}

void MovingMapObject::set_velocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void MovingMapObject::set_position(sf::Vector2f pos)
{
    m_pos = pos;
}

void MovingMapObject::set_forces(sf::Vector2f forces)
{
    m_forces = forces;
}

sf::Vector2f MovingMapObject::get_velocity() const
{
    return m_velocity;
}

sf::Vector2f MovingMapObject::get_position() const
{
    return m_pos;
}

sf::Vector2f MovingMapObject::get_forces() const
{
    return m_forces;
}

float MovingMapObject::get_radius() const
{
    return m_radius;
}

bool MovingMapObject::collision_object(MovingMapObject *otherObject)
{
    return true;
}

float MovingMapObject::collision_map()
{

    sf::Vector2i closestPoint = {(int) -m_radius, (int) -m_radius};
    float hit_angle = 0;
    int num_of_pixels = 0;

    for (int i = (int) -m_radius; i < (int) m_radius; ++i)
    {
        for (int j = (int) -m_radius; j < (int) m_radius; ++j)
        {
            if (i * i + j * j <= (int) (m_radius * m_radius) &&
                (i != 0 || j != 0))
            {

                sf::Vector2i pos = {(int) m_pos.x + i, (int) m_pos.y + j};
                if (pos.x < 0 || pos.y < 0 || pos.x >= m_map->getSize().x ||
                    pos.y >= m_map->getSize().y)
                {
                    continue;
                }
                if (m_map->getPixel(pos.x, pos.y) == sf::Color::White)
                {
                    if (i * i + j * j < closestPoint.x * closestPoint.x +
                                        closestPoint.y * closestPoint.y)
                    {
                        closestPoint.x = i;
                        closestPoint.y = j;
                    }
                    hit_angle += (float) atan2(j, i);
                    num_of_pixels++;
                }
            }
        }
    }

    if (num_of_pixels == 0)
    {
        return -1;
    }

    float to_move = m_radius - (float) sqrt(
            closestPoint.x * closestPoint.x +
            closestPoint.y * closestPoint.y);
    m_pos.x -= to_move * (float) cos(atan2(closestPoint.y, closestPoint.x));
    m_pos.y -= to_move * (float) sin(atan2(closestPoint.y, closestPoint.x));
//        
    hit_angle /= (float) num_of_pixels;
    float velocity_angle = atan2(m_velocity.y, m_velocity.x);
    float angle_diff = hit_angle - velocity_angle;

    float velocity_norm_length = -(float) sqrt(m_velocity.x * m_velocity.x +
                                               m_velocity.y * m_velocity.y) *
                                 (float) cos(angle_diff);
    velocity_norm_length *= 0.8f;


    float velocity_tang_length = -(float) sqrt(m_velocity.x * m_velocity.x +
                                               m_velocity.y * m_velocity.y) *
                                 (float) sin(angle_diff);

    if (abs(velocity_tang_length) < abs(FRICTION * velocity_norm_length))
    {
        velocity_tang_length = 0;
    }
    else if (velocity_tang_length > 0)
    {
        velocity_tang_length -= abs(FRICTION * velocity_norm_length);
    }
    else
    {
        velocity_tang_length += abs(FRICTION * velocity_norm_length);
    }
    sf::Vector2f velocity_norm = {
            (float) cos(hit_angle) * velocity_norm_length,
            (float) sin(hit_angle) * velocity_norm_length};


    sf::Vector2f velocity_tang = {
            (float) cos(hit_angle + PI / 2) * velocity_tang_length,
            (float) sin(hit_angle + PI / 2) * velocity_tang_length};

    m_velocity = velocity_norm + velocity_tang;

    if (hit_angle > PI / 2 - 0.001 && hit_angle < PI / 2 + 0.001 &&
        abs(velocity_norm_length) + abs(velocity_tang_length) < GRAVITY / 2)
    {
        m_resting = true;
    }

    return hit_angle;
}

bool MovingMapObject::is_alive() const
{
    return m_alive;
}

void MovingMapObject::kill()
{
    if (m_alive)
    {
        on_death();
    }
    m_alive = false;
}

bool MovingMapObject::is_rest() const
{
    return m_resting;
}

void MovingMapObject::collide_generic(MovingMapObject *otherObject)
{
    // get the angle of the collision
    float angle = atan2(otherObject->get_position().y - m_pos.y,
                        otherObject->get_position().x - m_pos.x);
    // get the velocity_length in the collision direction
    float velocity_length = sqrt(m_velocity.x * m_velocity.x +
                                 m_velocity.y * m_velocity.y);
    float other_velocity_length = sqrt(
            otherObject->get_velocity().x * otherObject->get_velocity().x +
            otherObject->get_velocity().y * otherObject->get_velocity().y);

    float velocity_angle = atan2(m_velocity.y, m_velocity.x);
    float other_velocity_angle = atan2(otherObject->get_velocity().y,
                                       otherObject->get_velocity().x);

    float velocity_length_norm =
            (float) cos(velocity_angle - angle) * velocity_length;
    float velocity_length_tang =
            (float) sin(velocity_angle - angle) * velocity_length;
    float other_velocity_length_norm =
            (float) cos(other_velocity_angle - angle) * other_velocity_length;
    float other_velocity_length_tang =
            (float) sin(other_velocity_angle - angle) * other_velocity_length;

    float new_velocity_length_norm =
            (velocity_length_norm * (m_weight - otherObject->m_weight) +
             2 * otherObject->m_weight * other_velocity_length_norm) /
            (m_weight + otherObject->m_weight);
    float new_other_velocity_length_norm =
            (other_velocity_length_norm * (otherObject->m_weight - m_weight) +
             2 * m_weight * velocity_length_norm) /
            (m_weight + otherObject->m_weight);

    m_velocity = {
            (float) cos(angle) * new_velocity_length_norm +
            (float) cos(angle + PI / 2) * velocity_length_tang,
            (float) sin(angle) * new_velocity_length_norm +
            (float) sin(angle + PI / 2) * velocity_length_tang
    };
    otherObject->m_velocity = {
            (float) cos(angle) * new_other_velocity_length_norm +
            (float) cos(angle + PI / 2) * other_velocity_length_tang,
            (float) sin(angle) * new_other_velocity_length_norm +
            (float) sin(angle + PI / 2) * other_velocity_length_tang
    };

    otherObject->m_resting = false;
    m_resting = false;

    m_pos.x = otherObject->get_position().x -
              (float) cos(angle) * (m_radius + otherObject->m_radius);
    m_pos.y = otherObject->get_position().y -
              (float) sin(angle) * (m_radius + otherObject->m_radius);
}

bool MovingMapObject::collide_dd(Ball *otherObject)
{
    return false;
}

sf::Image *MovingMapObject::get_map()
{
    return m_map;
}

void MovingMapObject::exploded(const Bomb &bomb)
{
    float distance = sqrt(
            (m_pos.x - bomb.pos.x) * (m_pos.x - bomb.pos.x) +
            (m_pos.y - bomb.pos.y) * (m_pos.y - bomb.pos.y));

    if (distance < bomb.radius + m_radius)
    {
        float force =
                (bomb.force * atan2(bomb.radius, distance) / PI) / m_weight;
        float angle = atan2(m_pos.y - bomb.pos.y, m_pos.x - bomb.pos.x);
        m_velocity.x += (float) cos(angle) * force;
        m_velocity.y += (float) sin(angle) * force;
        m_resting = false;


    }

}
