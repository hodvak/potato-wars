#pragma once

#include "StoneThrowCreator.h"
#include "MapObject/Grenade.h"
#include "Weapon/ThrowWeapon.h"

class GrenadeCreator : public StoneThrowCreator
{
    public:
    GrenadeCreator(int amount,
                   GameMap *map,
                   const std::function<void(
                           std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                   BombHandler *bombHandler) :
            StoneThrowCreator(amount, map, addMapObjectFunc),
            m_bombHandler(bombHandler),m_addMapObjectFunc(addMapObjectFunc)
    {}

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override
    {
        std::unique_ptr<Grenade> grenade= std::make_unique<Grenade>(
                character.getPosition(),

                getMap(),

                m_bombHandler
                );
        return std::make_unique<ThrowWeapon>(character,std::move(grenade) ,m_addMapObjectFunc
                                             );
    }

private:
    BombHandler *m_bombHandler;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
};