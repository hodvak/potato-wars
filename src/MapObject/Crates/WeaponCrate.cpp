#include "MapObject/Crates/WeaponCrate.h"

WeaponCrate::WeaponCrate(MapVector pos, GameMap *map,
                         std::unique_ptr<WeaponCreator> &&weaponCreator) :
        Crate(pos, map, weaponCreator->getTexture(),
              weaponCreator->getTextureRect()),
        m_weaponCreator(std::move(weaponCreator))
{

}

bool WeaponCrate::collideDD2(Character *other_object)
{
    other_object->addWeaponCreator(std::move(m_weaponCreator));
    kill();
    return true;
}
