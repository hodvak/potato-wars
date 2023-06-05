#include "MapObject/MovingMapObject.h"
#include <cmath>
#include "Physics.h"
#include "Const.h"


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
          m_forces(0, m_weight * Physics::GRAVITY),
          m_resting(false),
          m_alive(true),
          m_map(map),
          m_bombHandler(bomb_handler),
          m_rotation(0)
{
}


void MovingMapObject::updateVelocity(const sf::Time &deltaTime)
{
    m_velocity += m_forces / m_weight * deltaTime.asSeconds();
}

void MovingMapObject::updateForces(const sf::Time &deltaTime)
{
    m_forces = {0, m_weight * Physics::GRAVITY};
}

void MovingMapObject::updatePosition(const sf::Time &deltaTime)
{
    m_pos += m_velocity * deltaTime.asSeconds();
}

void MovingMapObject::update(const sf::Time &deltaTime)
{
    if (!m_resting)
    {
        updateForces(deltaTime);
        updateVelocity(deltaTime);
        updatePosition(deltaTime);
        updateRotation(deltaTime);
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

    if (tang.getMagnitude() < Physics::FRICTION * norm.getMagnitude())
    {
        tang = {0, 0};
    }
    else
    {
        float ang = tang.getAngle();
        float mag = tang.getMagnitude() - norm.getMagnitude() * Physics::FRICTION;
        tang = MapVector::getVectorFromAngle(ang, mag);
    }

    if (hit_angle > Consts::PI / 2 - 0.001 && hit_angle < Consts::PI / 2 + 0.001 &&
        abs(norm.getMagnitude()) + abs(tang.getMagnitude()) < Physics::GRAVITY / 2)
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
    if(!other_object->isAlive() || !isAlive())
    {
        return;
    }
    float angle = (other_object->m_pos - m_pos).getAngle();

    auto [v1f, v2f] = Physics::elasticCollision(m_weight,
                                                other_object->m_weight,
                                                m_velocity,
                                                other_object->m_velocity,
                                                angle);
    m_velocity = v1f;
    other_object->m_velocity = v2f;

    other_object->m_resting = false;
    m_resting = false;

    m_pos = other_object->m_pos +
            MapVector::getVectorFromAngle(angle + Consts::PI,
                                          m_radius +
                                          other_object->m_radius);
}


const GameMap *MovingMapObject::getMap() const
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
                      (Consts::PI * m_weight);
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

void MovingMapObject::updateRotation(const sf::Time &deltaTime)
{
    m_rotation += m_velocity.x * 0.11f * deltaTime.asSeconds();
    m_rotation = fmod(m_rotation, 2 * Consts::PI);
}

float MovingMapObject::getRotation() const
{
    return m_rotation;
}

void MovingMapObject::setRotation(float rotation)
{
    m_rotation = rotation;
}

bool MovingMapObject::collideDD(Projectile *)
{
    return false;
}

bool MovingMapObject::collideDD(Character *)
{
    return false;
}

bool MovingMapObject::intersect(const MovingMapObject &other_object) const
{
    return (m_pos - other_object.m_pos).getMagnitude() <
           m_radius + other_object.m_radius;
}
