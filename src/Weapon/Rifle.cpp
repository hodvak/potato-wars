#include "Weapon/Rifle.h"
#include "MapObject/Projectile.h"
#include "resources_manager.h"

Rifle::Rifle(const Character &owner,
             const std::function<void(std::unique_ptr<MovingMapObject> &&)>
             &addMapObjectFunc,
             const GameMap &map,
             BombHandler &bombHandler) :
        Gun(owner,
            addMapObjectFunc,
            map,
            bombHandler,
            resources_manager::IMG_RIFLE_PATH,
            resources_manager::IMG_RIFLE_SIZE),
        m_character(owner)
{

}


void Rifle::handleMousePressed(const MapVector &mousePosition)
{
    MapVector power = mousePosition - m_character.getPosition();
    
    // todo: magic number 700
    power.normalize(700);
    
    shot(power, 0.9, 30, 3);
    // todo: magic numbers? 30, 3, 0.6 ?
    endTurn();
    die();
}