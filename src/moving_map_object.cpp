#include "moving_map_object.h"
#include <cmath>

const float PI = acos(-1.0f);
const float MovingMapObject::GRAVITY = 130;
const float MovingMapObject::FRICTION = 0.2;

MovingMapObject::MovingMapObject(float weight,
                                 MapVector pos,
                                 Map *map,
                                 float radius,
                                 MapVector start_velocity,
                                 BombHandler *bomb_handler)
        : m_weight(weight),
          m_velocity(start_velocity),
          m_pos(pos),
          m_radius(radius),
          m_forces(0, m_weight * GRAVITY),
          m_resting(false),
          m_alive(true),
          m_map(map),
          m_bomb_handler(bomb_handler)
{
}

void MovingMapObject::update_velocity(float delta_time)
{
    m_velocity += m_forces / m_weight * delta_time;
}

void MovingMapObject::update_forces(float)
{
    m_forces = {0, m_weight * GRAVITY};
}

void MovingMapObject::update_position(float delta_time)
{
    m_pos += m_velocity * delta_time;
}

void MovingMapObject::update(float delta_time)
{
    if (!m_resting)
    {
        update_forces(delta_time);
        update_velocity(delta_time);
        update_position(delta_time);
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

bool MovingMapObject::collision_object(MovingMapObject *)
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

                sf::Vector2i pos = {(int)m_pos.x + i,
                                    (int)m_pos.y + j};
                if (pos.x < 0 ||
                    pos.y < 0 ||
                    pos.x >= (int) m_map->get_mask()->getSize().x ||
                    pos.y >= (int) m_map->get_mask()->getSize().y)
                {
                    continue;
                }
                if (m_map->get_mask()->getPixel(pos.x, pos.y) ==
                    sf::Color::White)
                {
                    if (i * i + j * j <
                        closestPoint.x * closestPoint.x +
                        closestPoint.y * closestPoint.y)
                    {
                        closestPoint.x = (float)i;
                        closestPoint.y = (float)j;
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
    float to_move = m_radius - closestPoint.get_magnitude();
    m_pos -= MapVector::get_vector_from_angle(closestPoint.get_angle(), to_move);

    //fix the hit angle (average hit angle)
    hit_angle /= (float) num_of_pixels;


    auto [norm, tang] = m_velocity.get_split_vector(hit_angle);

    norm *= -1.0f; //bounce back

    norm *= 0.8f; // fraction (kind of) todo:fix consts

    if (tang.get_magnitude() < FRICTION * norm.get_magnitude())
    {
        tang = {0, 0};
    }
    else
    {
        float ang = tang.get_angle();
        float mag = tang.get_magnitude() - norm.get_magnitude() * FRICTION;
        tang = MapVector::get_vector_from_angle(ang, mag);
    }

    if (hit_angle > PI / 2 - 0.001 && hit_angle < PI / 2 + 0.001 &&
        abs(norm.get_magnitude()) + abs(tang.get_magnitude()) < GRAVITY / 2)
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
    float angle = (otherObject->m_pos - m_pos).get_angle();

    auto [my_norm, my_tang] = m_velocity.get_split_vector(angle);
    auto [other_norm, other_tang] = otherObject->m_velocity.get_split_vector(
            angle);

    float new_velocity_length_norm =
            (my_norm.get_magnitude() * (m_weight - otherObject->m_weight) +
             2 * otherObject->m_weight * other_norm.get_magnitude()) /
            (m_weight + otherObject->m_weight);

    float new_other_velocity_length_norm =
            (other_norm.get_magnitude() * (otherObject->m_weight - m_weight) +
             2 * m_weight * my_norm.get_magnitude()) /
            (m_weight + otherObject->m_weight);

    my_norm = -MapVector::get_vector_from_angle(my_norm.get_angle(),
                                                new_velocity_length_norm);
    other_norm = -MapVector::get_vector_from_angle(other_norm.get_angle(),
                                                   new_other_velocity_length_norm);

    m_velocity = my_norm + my_tang;
    otherObject->m_velocity = other_norm + other_tang;

    otherObject->m_resting = false;
    m_resting = false;

    m_pos = otherObject->m_pos +
            MapVector::get_vector_from_angle(PI + angle,
                                             m_radius +
                                             otherObject->m_radius);
}

bool MovingMapObject::collide_dd(Ball *)
{
    return false;
}

Map *MovingMapObject::get_map()
{
    return m_map;
}

void MovingMapObject::exploded(const Bomb &bomb)
{
    MapVector diff = m_pos - bomb.pos;
    float distance = diff.get_magnitude();
    if (distance < (float)bomb.radius + m_radius)
    {
        float force = bomb.force * (float)atan2(bomb.radius, distance) / (PI * m_weight);
        m_velocity += MapVector::get_vector_from_angle(diff.get_angle(), force);
        m_resting = false;
    }
}

void MovingMapObject::add_bomb(const Bomb &bomb)
{
    m_bomb_handler->add_bomb(bomb);
}

void
MovingMapObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape shape;

    shape.setRadius(m_radius);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(m_pos.x, m_pos.y);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);
    target.draw(shape);
}
