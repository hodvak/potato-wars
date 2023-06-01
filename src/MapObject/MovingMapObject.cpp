#include "MapObject/MovingMapObject.h"
#include <cmath>

const float PI = acos(-1.0f);
const float MovingMapObject::GRAVITY = 130.0f;
const float MovingMapObject::FRICTION = 0.2f;


MovingMapObject::MovingMapObject(float weight,
                                 MapVector pos,
                                 GameMap *map,
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
          m_bombHandler(bomb_handler),
          m_rotation(0)
{
}


void MovingMapObject::updateVelocity(float delta_time)
{
    m_velocity += m_forces / m_weight * delta_time;
}

void MovingMapObject::updateForces(float)
{
    m_forces = {0, m_weight * GRAVITY};
}

void MovingMapObject::updatePosition(float delta_time)
{
    m_pos += m_velocity * delta_time;
}

void MovingMapObject::update(float delta_time)
{
    if (!m_resting)
    {
        updateForces(delta_time);
        updateVelocity(delta_time);
        updatePosition(delta_time);
        updateRotation(delta_time);
        collisionMap();

    }
}

void MovingMapObject::setVelocity(MapVector velocity)
{
    m_velocity = velocity;
}

void MovingMapObject::setPosition(MapVector pos)
{
    m_pos = pos;
}

void MovingMapObject::setForces(MapVector forces)
{
    m_forces = forces;
}

MapVector MovingMapObject::getVelocity() const
{
    return m_velocity;
}

MapVector MovingMapObject::getPosition() const
{
    return m_pos;
}

MapVector MovingMapObject::getForces() const
{
    return m_forces;
}

float MovingMapObject::getRadius() const
{
    return m_radius;
}

bool MovingMapObject::collisionObject(MovingMapObject *other_object)
{
    return true;
}

float MovingMapObject::collisionMap()
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

                sf::Vector2i pos = {(int) m_pos.x + i,
                                    (int) m_pos.y + j};
                if (pos.x < 0 ||
                    pos.y < 0 ||
                    pos.x >= (int) m_map->getMask().getSize().x ||
                    pos.y >= (int) m_map->getMask().getSize().y)
                {
                    continue;
                }
                if (m_map->getMask().getPixel(pos.x, pos.y) ==
                    sf::Color::White)
                {
                    if (i * i + j * j <
                        closestPoint.x * closestPoint.x +
                        closestPoint.y * closestPoint.y)
                    {
                        closestPoint.x = (float) i;
                        closestPoint.y = (float) j;
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
    m_pos -= MapVector::getVectorFromAngle(closestPoint.getAngle(),
                                           to_move);

    //fix the hit angle (average hit angle)
    hit_angle /= (float) num_of_pixels;


    auto [norm, tang] = m_velocity.getSplitVector(hit_angle);

    norm *= -1.0f; //bounce back

    norm *= 0.8f; // fraction (kind of) todo:fix consts

    if (tang.getMagnitude() < FRICTION * norm.getMagnitude())
    {
        tang = {0, 0};
    }
    else
    {
        float ang = tang.getAngle();
        float mag = tang.getMagnitude() - norm.getMagnitude() * FRICTION;
        tang = MapVector::getVectorFromAngle(ang, mag);
    }

    if (hit_angle > PI / 2 - 0.001 && hit_angle < PI / 2 + 0.001 &&
        abs(norm.getMagnitude()) + abs(tang.getMagnitude()) < GRAVITY / 2)
    {
        m_resting = true;
    }

    m_velocity = norm + tang;

    return hit_angle;
}


bool MovingMapObject::isAlive() const
{
    return m_alive;
}

void MovingMapObject::kill()
{
    if (m_alive)
    {
        onDeath();
    }
    m_alive = false;
}

bool MovingMapObject::isRest() const
{
    return m_resting;
}

void MovingMapObject::collideGeneric(MovingMapObject *other_object)
{
    // get the angle of the collision
    float angle = (other_object->m_pos - m_pos).getAngle();

    auto [my_norm, my_tang] = m_velocity.getSplitVector(angle);
    auto [other_norm, other_tang] = other_object->m_velocity.getSplitVector(
            angle);

    float new_velocity_length_norm =
            (my_norm.getMagnitude() * (m_weight - other_object->m_weight) +
             2 * other_object->m_weight * other_norm.getMagnitude()) /
            (m_weight + other_object->m_weight);

    float new_other_velocity_length_norm =
            (other_norm.getMagnitude() * (other_object->m_weight - m_weight) +
             2 * m_weight * my_norm.getMagnitude()) /
            (m_weight + other_object->m_weight);

    my_norm = -MapVector::getVectorFromAngle(my_norm.getAngle(),
                                             new_velocity_length_norm);
    other_norm = -MapVector::getVectorFromAngle(other_norm.getAngle(),
                                                new_other_velocity_length_norm);

    m_velocity = my_norm + my_tang;
    other_object->m_velocity = other_norm + other_tang;

    other_object->m_resting = false;
    m_resting = false;

    m_pos = other_object->m_pos +
            MapVector::getVectorFromAngle(PI + angle,
                                          m_radius +
                                          other_object->m_radius);
}

bool MovingMapObject::collideDD(Ball *)
{
    return false;
}

GameMap *MovingMapObject::getMap()
{
    return m_map;
}

void MovingMapObject::exploded(const Bomb &bomb)
{
    MapVector diff = m_pos - bomb.pos;
    float distance = diff.getMagnitude();
    if (distance < (float) bomb.radius + m_radius)
    {
        float force = bomb.force * (float) atan2(bomb.radius, distance) /
                      (PI * m_weight);
        m_velocity += MapVector::getVectorFromAngle(diff.getAngle(), force);
        m_resting = false;
    }
}

void MovingMapObject::addBomb(const Bomb &bomb)
{
    m_bombHandler->addBomb(bomb);
}

void
MovingMapObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    
}
void MovingMapObject::updateRotation(float delta_time)
{
    m_rotation += m_velocity.x * 0.11f * delta_time;
    m_rotation = fmod(m_rotation, 2 * PI);
}

float MovingMapObject::getRotation() const
{
    return m_rotation;
}

void MovingMapObject::setRotation(float rotation)
{
    m_rotation = rotation;
}