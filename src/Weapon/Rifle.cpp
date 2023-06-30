#include "Weapon/Rifle.h"
#include "MapObject/Projectile.h"
#include "resources_manager.h"

Rifle::Rifle(const Character &owner,
             GameHelperData &gameHelperData) :
        Gun(owner,
            resources_manager::IMG_RIFLE_PATH,
            resources_manager::IMG_RIFLE_SIZE,
            gameHelperData),
        m_character(owner)
{

}


void Rifle::handleMousePressed(const MapVector &mousePosition)
{
    MapVector power = mousePosition - m_character.getPosition();
    

    power.normalize(700);
    
    shot(power, 0.9, 30, 3);
    Weapon::getGameHelperData().addSound(resources_manager::SOUND_SNIPERSHOT_PATH);

    die();
}