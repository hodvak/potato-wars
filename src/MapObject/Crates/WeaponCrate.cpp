#include "MapObject/Crates/WeaponCrate.h"



WeaponCrate::WeaponCrate(const MapVector &pos,
                         std::unique_ptr<WeaponCreator> &&weaponCreator,
                         GameHelperData &gameHelperData) :
                         
        Crate(pos,
              weaponCreator->getTexture(),
              weaponCreator->getTextureRect(),
              gameHelperData
              ),
        m_weaponCreator(std::move(weaponCreator))
{

}

bool WeaponCrate::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}

bool WeaponCrate::collideDD2(Character &otherObject)
{
    otherObject.addWeaponCreator(std::move(m_weaponCreator));
    kill();
    return true;
}

