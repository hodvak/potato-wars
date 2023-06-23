#include "Weapon/Minigun.h"
#include "MapObject/Projectile.h"
#include "Resources_manager.h"

Minigun::Minigun(const Character &owner,
                 const std::function<void(std::unique_ptr<MovingMapObject> &&)>
                 &addMapObjectFunc,
                 const GameMap &map,
                 BombHandler &bombHandler) :
        Gun(owner,
            addMapObjectFunc,
            map,
            bombHandler,
            resources_manager::IMG_MINIGUN_PATH,
            resources_manager::IMG_MINIGUN_SIZE),
        m_character(owner),
        m_aimPosition(0, 0),
        m_timePassed(sf::Time::Zero),
        m_firing(false),
        m_bulletsFired(0)
{

}

void Minigun::handleMousePressed(const MapVector &mousePosition)
{
    m_aimPosition = mousePosition;
    m_firing = true;
}

void Minigun::update(const sf::Time &deltaTime)
{
    Gun::update(deltaTime);
    if (m_firing)
    {
        m_timePassed += deltaTime;
        if (m_timePassed >= sf::seconds(0.1))
        {
            m_timePassed -= sf::seconds(0.1);
            m_bulletsFired++;
            
            MapVector power = m_aimPosition - m_character.getPosition();
            
            float randomAngle;
            // random number between 0 and 1 with 0.01 step
            randomAngle = (rand() % 100) / 100.0f;
            randomAngle *= BULLETS_ANGLE;
            randomAngle -= BULLETS_ANGLE / 2;
            randomAngle += power.getAngle();
            
            power = MapVector::getVectorFromAngle(randomAngle, 700);
            shot(power, 0.3, 30, 3);

            if (m_bulletsFired == BULLETS_COUNT)
            {
                die();
            }
        }
    }
}

void Minigun::handleMouseMoved(const MapVector &mousePosition)
{
    Gun::handleMouseMoved(mousePosition);
    m_aimPosition = mousePosition;
}
