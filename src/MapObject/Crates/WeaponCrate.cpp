#include "MapObject/Crates/WeaponCrate.h"

// todo: understand why the warning about non-virtual destructor

WeaponCrate::WeaponCrate(const MapVector &pos,
                         std::unique_ptr<WeaponCreator> &&weaponCreator,
                         const GameMap &map,
                         BombHandler &bombHandler) :
                         
        Crate(pos,
              weaponCreator->getTexture(),
              weaponCreator->getTextureRect(),
              map,
              bombHandler
              ),
        m_weaponCreator(std::move(weaponCreator))
{

}

bool WeaponCrate::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}

bool WeaponCrate::collideDD2(Character &other_object)
{
    other_object.addWeaponCreator(std::move(m_weaponCreator));
    kill();
    return true;
}

