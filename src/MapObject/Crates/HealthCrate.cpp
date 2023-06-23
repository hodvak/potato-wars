#include "MapObject/Crates/HealthCrate.h"
#include "resources_manager.h"

// todo: add consts for number and texture path
HealthCrate::HealthCrate(const MapVector &pos,
                         const GameMap &map,
                         BombHandler &bombHandler) :
        Crate(pos,
              resources_manager::get<sf::Texture>("resources/images/Textures/health2.png"),
              sf::IntRect(0, 
                          0,
                          resources_manager::get<sf::Texture>("resources/images/Textures/health2.png").getSize().x,
                          resources_manager::get<sf::Texture>("resources/images/Textures/health2.png").getSize().y),
                          map,
                          bombHandler),
        health(50) // todo: health unused?
{
    
}

bool HealthCrate::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}
bool HealthCrate::collideDD2(Character &otherObject)
{
    // todo: add consts
    otherObject.damage(-0.5);
    kill();
    return true;
}


