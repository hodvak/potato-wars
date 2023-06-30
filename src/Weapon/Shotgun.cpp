#include <numbers>
#include "Weapon/Shotgun.h"
#include "MapObject/Projectile.h"
#include "resources_manager.h"

Shotgun::Shotgun(const Character &owner, GameHelperData &gameHelperData) :
        Gun(owner,
            resources_manager::IMG_SHOTGUN_PATH,
            resources_manager::IMG_SHOTGUN_SIZE,
            gameHelperData),
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


        shot(temp, 0.3, 30, 3);
    }
    getGameHelperData().addSound(resources_manager::SOUND_SHOTGUN_PATH);
    die();
}
