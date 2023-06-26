#include "Weapon/Weapon.h"

Weapon::Weapon(GameHelperData &gameHelperData):
    m_gameHelperData(gameHelperData),
    m_isAlive(true)
{

}

void Weapon::die()
{
    m_isAlive = false;
}

bool Weapon::isAlive() const
{
    return m_isAlive;
}

bool Weapon::turnEnder() const
{
    return true;
}

GameHelperData &Weapon::getGameHelperData() const
{
    return m_gameHelperData;
}


