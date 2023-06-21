#include <numbers>
#include "Weapon/Shotgun.h"
#include "MapObject/Projectile.h"

Shotgun::Shotgun(const Character &owner,
                 const std::function<void(std::unique_ptr<MovingMapObject> &&)>
                 &addMapObjectFunc,
                 const GameMap &map,
                 BombHandler &bombHandler) :
        Weapon(),
        m_character(owner),
        m_aimPosition(0, 0),
        m_texture(owner.getColor(),
                  owner.getPosition(),
                  {0, 0},
                  owner.getRadius()),
        m_addMapObjectFunc(addMapObjectFunc),
        m_map(map),
        m_bombHandler(bombHandler)
{

}

void Shotgun::handleMouseMoved(const MapVector &mousePosition)
{
    m_aimPosition = mousePosition;
    m_texture.setAimPosition(mousePosition);
}

void Shotgun::handleMousePressed(const MapVector &mousePosition)
{
    m_aimPosition = mousePosition;
    m_texture.setAimPosition(mousePosition);
    MapVector power = m_aimPosition - m_character.getPosition();

    // todo: magic number 700
    power.normalize(700);
    
    for (int i = 0; i < 5; i++)
    {
        float randomAngle;
        // random number between 0 and 1 with 0.01 step
        randomAngle = (rand() % 100) / 100.0f; 
        randomAngle *= 3.0f / 20.0f * std::numbers::pi_v<float>;
        randomAngle -= 3.0f / 40.0f * std::numbers::pi_v<float>;
        randomAngle += power.getAngle();
        
        MapVector temp = MapVector::getVectorFromAngle(randomAngle, power.getMagnitude());

        MapVector startPosition = temp;
        startPosition.normalize(m_character.getRadius() + 6);
        startPosition = m_character.getPosition() + startPosition;
        // todo: magic number .... 
        
        m_addMapObjectFunc(
                std::make_unique<Projectile>(30,
                                             startPosition,
                                             3,
                                             0.3,
                                             temp,
                                             m_map,
                                             m_bombHandler));


    }
    // todo: magic numbers? 30, 3, 0.6 ?
    die();
}

void Shotgun::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_texture, states);
}

void Shotgun::update(const sf::Time &deltaTime)
{
    m_texture.setPosition(m_character.getPosition());
}
