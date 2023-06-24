#include "Weapon/Weapon.h"

Weapon::Weapon():
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


