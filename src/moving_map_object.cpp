#include "moving_map_object.h"
#include <cmath>
#include <iostream>


const double PI = acos(-1.0);

MovingMapObject::MovingMapObject(float weight,
                                 MapVector pos,
                                 Map *map,
                                 float radius,
                                 MapVector startVelocity,
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
    MapVector cameraOffset = {cameraRect.left, cameraRect.top};
    MapVector cameraRatio = {(float) target.getSize().x / cameraRect.width,
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

void MovingMapObject::update(float deltaTime, Map *map)
{
    if (!m_resting)
    {
        update_forces(deltaTime);
        update_velocity(deltaTime);
        update_position(deltaTime);
        collision_map();

    }
}

void MovingMapObject::set_velocity(MapVector velocity)
{
    m_velocity = velocity;
}

void MovingMapObject::set_position(MapVector pos)
{
    m_pos = pos;
}

void MovingMapObject::set_forces(MapVector forces)
{
    m_forces = forces;
}

MapVector MovingMapObject::get_velocity() const
{
    return m_velocity;
}

MapVector MovingMapObject::get_position() const
{
    return m_pos;
}

MapVector MovingMapObject::get_forces() const
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

    MapVector closestPoint = {-m_radius, -m_radius};
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
                if (pos.x < 0 || pos.y < 0 || pos.x >= m_map->getMask()->getSize().x ||
                    pos.y >= m_map->getMask()->getSize().y)
                {
                    continue;
                }
                if (m_map->getMaskColor(pos.x, pos.y) == sf::Color::White)
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

    //move to stand on the closest point
    float to_move = m_radius - closestPoint.getMagnitude();
    m_pos -= MapVector::getVectorFromAngle(closestPoint.getAngle(), to_move);

    //fix the hit angle (average hit angle)
    hit_angle /= (float) num_of_pixels;


    auto [norm, tang] = m_velocity.getSplitVector(hit_angle);
    
    norm *= -1.0f; //bounce back

    norm *= 0.8f; // fraction (kind of) todo:fix consts
    
    if (tang.getMagnitude() < FRICTION * norm.getMagnitude())
    {
        tang = {0,0};
    }
    else
    {
        float ang = tang.getAngle();
        float mag = tang.getMagnitude() - norm.getMagnitude() * FRICTION;
        tang = MapVector::getVectorFromAngle(ang,mag);
    }
    
    if (hit_angle > PI / 2 - 0.001 && hit_angle < PI / 2 + 0.001 &&
        abs(norm.getMagnitude()) + abs(tang.getMagnitude()) < GRAVITY / 2)
    {
        m_resting = true;
    }

    m_velocity = norm + tang;

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
    float angle = (otherObject->m_pos - m_pos).getAngle();

    auto [my_norm, my_tang] = m_velocity.getSplitVector(angle);
    auto [other_norm, other_tang] = otherObject->m_velocity.getSplitVector(angle);
    
    float new_velocity_length_norm =
            (my_norm.getMagnitude() * (m_weight - otherObject->m_weight) +
             2 * otherObject->m_weight * other_norm.getMagnitude()) /
            (m_weight + otherObject->m_weight);
    
    float new_other_velocity_length_norm =
            (other_norm.getMagnitude() * (otherObject->m_weight - m_weight) +
             2 * m_weight * my_norm.getMagnitude()) /
            (m_weight + otherObject->m_weight);
    
    my_norm = -MapVector::getVectorFromAngle(my_norm.getAngle(), new_velocity_length_norm);
    other_norm = -MapVector::getVectorFromAngle(other_norm.getAngle(), new_other_velocity_length_norm);
    
    m_velocity = my_norm + my_tang;
    otherObject->m_velocity = other_norm + other_tang;
    
    otherObject->m_resting = false;
    m_resting = false;

    m_pos = otherObject->m_pos+MapVector::getVectorFromAngle(PI + angle, m_radius+otherObject->m_radius);
}

bool MovingMapObject::collide_dd(Ball *otherObject)
{
    return false;
}

Map *MovingMapObject::get_map()
{
    return m_map;
}

void MovingMapObject::exploded(const Bomb &bomb)
{
//    MapVector diff = m_pos - bomb.pos;
//    float distance = diff.getMagnitude();
//    if (distance < bomb.radius + m_radius)
//    {
//        float force = bomb.force * atan2(bomb.radius, distance) / (PI * m_weight);
//        m_velocity += MapVector::getVectorFromAngle(diff.getAngle(), force);
//        m_resting = false;
//    }
}

void MovingMapObject::addBomb(const Bomb &bomb)
{
    m_bombHandler->addBomb(bomb);
}