#include <numbers>
#include "Weapon/Shotgun.h"
#include "MapObject/Projectile.h"
#include "resources_manager.h"

Shotgun::Shotgun(const Character &owner,
                 const std::function<void(std::unique_ptr<MovingMapObject> &&)>
                 &addMapObjectFunc,
                 const GameMap &map,
                 BombHandler &bombHandler) :
        Gun(owner,
            addMapObjectFunc,
            map,
            bombHandler,
            resources_manager::IMG_SHOTGUN_PATH,
            resources_manager::IMG_SHOTGUN_SIZE),
        m_character(owner)
{

}

void Shotgun::handleMousePressed(const MapVector &mousePosition)
{
    
    MapVector power = mousePosition - m_character.getPosition();
    
    for (int i = 0; i < BULLETS_COUNT; i++)
    {
        float randomAngle;
        // random number between 0 and 1 with 0.01 step
        randomAngle = (rand() % 100) / 100.0f; 
        randomAngle *= BULLETS_ANGLE;
        randomAngle -= BULLETS_ANGLE / 2;
        randomAngle += power.getAngle();
        
        MapVector temp = MapVector::getVectorFromAngle(randomAngle, 700);

        // todo: magic numbers? 30, 3, 0.6 ?
        shot(temp, 0.3, 30, 3);
    }
    die();
}
