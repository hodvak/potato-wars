#include "MapObject/Crates/HealthCrate.h"
#include "resources_manager.h"

HealthCrate::HealthCrate(MapVector pos, GameMap *map) :
        Crate(pos, map, resources_manager::getTexture(
                "resources/images/Textures/health2.png"), sf::IntRect(0, 0,
                                                                         resources_manager::getTexture(
                                                                                 "resources/images/Textures/health2.png")->getSize().x,
                                                                         resources_manager::getTexture(
                                                                                 "resources/images/Textures/health2.png")->getSize().y))
{
    health = 50;
}

bool HealthCrate::collideDD2(Character *other_object)
{
    other_object->damage(-0.5);
    kill();
    return true;
}

