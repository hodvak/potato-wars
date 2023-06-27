#include "MapObject/Crates/HealthCrate.h"
#include "resources_manager.h"



HealthCrate::HealthCrate(const MapVector &pos,
                         GameHelperData &gameHelperData,float health):
        Crate(pos,
              resources_manager::get<sf::Texture>(resources_manager::IMG_HEALTH_PATH),
              sf::IntRect(0, 
                          0,
                          (int)resources_manager::get<sf::Texture>(resources_manager::IMG_HEALTH_PATH).getSize().x,
                          (int)resources_manager::get<sf::Texture>(resources_manager::IMG_HEALTH_PATH).getSize().y),
                          gameHelperData),
        health(health)
{
    
}

bool HealthCrate::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}
bool HealthCrate::collideDD2(Character &otherObject)
{

    otherObject.damage(-health/100);
    kill();
    return true;
}


