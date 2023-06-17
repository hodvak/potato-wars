#include "MapObject/MovingMapObject.h"
#include <numbers>
#include "Physics.h"


MovingMapObject::MovingMapObject(const MapVector &pos,
                                 float radius,
                                 float weight,
                                 const GameMap &map,
                                 BombHandler &bombHandler,
                                 const MapVector &startVelocity)
        : m_weight(weight),
          m_velocity(startVelocity),
          m_pos(pos),
          m_radius(radius),
          m_forces(0, m_weight * Physics::GRAVITY),
          m_resting(false),
          m_alive(true),
          m_map(map),
          m_bombHandler(bombHandler),
          m_rotation(0),
          m_stuckPoint(pos),
          m_movementTime(sf::Time::Zero)
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
    MapVector direction = m_pos; //save the old position

    m_pos += m_velocity * deltaTime.asSeconds(); //update the position

    
    
    direction = m_pos - m_stuckPoint; //get the direction for the stuck point
    direction *= deltaTime.asSeconds();

    //check if the object is stuck
    float maxDistance = 50 * deltaTime.asSeconds();
    if (direction.getMagnitude() > maxDistance)
    {
        direction.normalize(maxDistance);
        m_stuckPoint += direction;
    }
    else
    {
        m_stuckPoint += direction;
    }

    if ((m_pos - m_stuckPoint).getMagnitude() >= m_radius)
    {
        m_movementTime = sf::Time::Zero;
    }
    else
    {
        m_movementTime += deltaTime;
    }
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

void MovingMapObject::setVelocity(const MapVector &velocity)
{
    m_velocity = velocity;
}

void MovingMapObject::setPosition(const MapVector &pos)
{
    m_pos = pos;
}

void MovingMapObject::setForces(const MapVector &forces)
{
    m_forces = forces;
}

const MapVector &MovingMapObject::getVelocity() const
{
    return m_velocity;
}

const MapVector &MovingMapObject::getPosition() const
{
    return m_pos;
}

const MapVector &MovingMapObject::getForces() const
{
    return m_forces;
}

float MovingMapObject::getRadius() const
{
    return m_radius;
}

bool MovingMapObject::collisionObject() const
{
    return true;
}

std::optional<float> MovingMapObject::collisionMap()
{

    MapVector closestPoint = {-m_radius, -m_radius};
    float hitAngle = 0;
    int numOfPixels = 0;

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
                    pos.x >= (int) m_map.getMask().getSize().x ||
                    pos.y >= (int) m_map.getMask().getSize().y)
                {
                    continue;
                }
                if (m_map.getMask().getPixel(pos.x, pos.y) ==
                    sf::Color::White)
                {
                    if (i * i + j * j <
                        closestPoint.x * closestPoint.x +
                        closestPoint.y * closestPoint.y)
                    {
                        closestPoint.x = (float) i;
                        closestPoint.y = (float) j;
                    }
                    hitAngle += (float) atan2(j, i);
                    numOfPixels++;
                }
            }
        }
    }

    if (numOfPixels == 0)
    {
        return std::nullopt;
    }

    //move to stand on the closest point
    float to_move = m_radius - closestPoint.getMagnitude();
    m_pos -= MapVector::getVectorFromAngle(closestPoint.getAngle(),
                                           to_move);

    //fix the hit angle (average hit angle)
    hitAngle /= (float) numOfPixels;


    auto [norm, tang] = m_velocity.getSplitVector(hitAngle);

    norm *= -1.0f; //bounce back

    norm *= 0.8f; // fraction (kind of) todo:fix consts

    if (tang.getMagnitude() < Physics::FRICTION * norm.getMagnitude())
    {
        tang = {0, 0};
    }
    else
    {
        float ang = tang.getAngle();
        float mag =
                tang.getMagnitude() - norm.getMagnitude() * Physics::FRICTION;
        tang = MapVector::getVectorFromAngle(ang, mag);
    }

    if (hitAngle > std::numbers::pi_v<float> / 2 - 0.001 &&
        hitAngle < std::numbers::pi_v<float> / 2 + 0.001 &&
        abs(norm.getMagnitude()) + abs(tang.getMagnitude()) <
        Physics::GRAVITY / 2)
    {
        m_resting = true;
    }

    m_velocity = norm + tang;

    return hitAngle;
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

void MovingMapObject::collideGeneric(MovingMapObject &otherObject)
{
    if (!otherObject.isAlive() || !isAlive())
    {
        return;
    }
    float angle = (otherObject.m_pos - m_pos).getAngle();

    auto [v1f, v2f] = Physics::elasticCollision(m_weight,
                                                otherObject.m_weight,
                                                m_velocity,
                                                otherObject.m_velocity,
                                                angle);
    m_velocity = v1f;
    otherObject.m_velocity = v2f;

    otherObject.m_resting = false;
    m_resting = false;

    m_pos = otherObject.m_pos +
            MapVector::getVectorFromAngle(angle + std::numbers::pi_v<float>,
                                          m_radius +
                                          otherObject.m_radius);
}


const GameMap &MovingMapObject::getMap() const
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
                      (std::numbers::pi_v<float> * m_weight);
        m_velocity += MapVector::getVectorFromAngle(diff.getAngle(), force);
        m_resting = false;
    }
}

void MovingMapObject::addBomb(const Bomb &bomb)
{
    m_bombHandler.addBomb(bomb);
}

void
MovingMapObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}

void MovingMapObject::updateRotation(const sf::Time &deltaTime)
{
    m_rotation += m_velocity.x * 0.11f * deltaTime.asSeconds();
    m_rotation = fmod(m_rotation, 2 * std::numbers::pi_v<float>);
}

float MovingMapObject::getRotation() const
{
    return m_rotation;
}

void MovingMapObject::setRotation(float rotation)
{
    m_rotation = rotation;
}

bool MovingMapObject::collideDD2(Projectile &otherObject)
{
    return false;
}

bool MovingMapObject::collideDD2(Character &otherObject)
{
    return false;
}

bool MovingMapObject::collideDD2(Rock &otherObject)
{
    return false;
}

void MovingMapObject::collide(MovingMapObject &otherObject)
{
    // no collision if one of the objects is dead
    if (!otherObject.isAlive() || !isAlive() || !intersect(otherObject))
    {
        return;
    }
    // if this object implements DD2
    if (collideDD1(otherObject))
    {
        return;
    }
    // if other object implements DD2
    if (otherObject.collideDD1(*this))
    {
        return;
    }
    // generic collision by default
    if(collisionObject())
    collideGeneric(otherObject);
}

bool MovingMapObject::intersect(const MovingMapObject &other_object) const
{
    return (m_pos - other_object.m_pos).getMagnitude() <
           m_radius + other_object.m_radius;
}

bool MovingMapObject::collideDD2(BombObject &other_object)
{
    return false;
}

const sf::Time &MovingMapObject::getMovementTime() const
{
    return m_movementTime;
}

void MovingMapObject::stop()
{
    m_resting = true;
    m_movementTime = sf::Time::Zero;
}

bool MovingMapObject::collideDD2(WeaponCrate &otherObject)
{
    return false;
}

bool MovingMapObject::collideDD2(HealthCrate &otherObject)
{
    return false;
}


const MapVector &MovingMapObject::getStuckPoint() const
{
    return m_stuckPoint;
}

BombHandler &MovingMapObject::getBombHandler() const
{
    return m_bombHandler;
}

void MovingMapObject::unrest()
{
    m_resting = false;
}
