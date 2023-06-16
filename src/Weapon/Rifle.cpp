#include "Weapon/Rifle.h"
#include "MapObject/Projectile.h"

Rifle::Rifle(const Character &owner,
             const std::function<void(std::unique_ptr<MovingMapObject> &&)>
             &addMapObjectFunc,
             const GameMap &map,
             BombHandler &bombHandler) :
        Weapon(),
        m_character(owner),
        m_aimPosition(0, 0),
        m_texture(owner.getColor(),
                  owner.getPosition(),
                  {0, 0},
                  owner.getRadius()),
        m_addMapObjectFunc(addMapObjectFunc),
        m_map(map),
        m_bombHandler(bombHandler)
{

}

void Rifle::handleMouseMoved(const MapVector &mousePosition)
{
    m_aimPosition = mousePosition;
    m_texture.setAimPosition(mousePosition);
}

void Rifle::handleMousePressed(const MapVector &mousePosition)
{
    m_aimPosition = mousePosition;
    m_texture.setAimPosition(mousePosition);
    MapVector power = m_aimPosition - m_character.getPosition();
    MapVector startPosition = power;

    // todo: magic number 700
    power.normalize(700);
    
    // todo: magic number 6 (calculate as 2 radius maybe?)
    startPosition.normalize(m_character.getRadius() + 6);
    startPosition = m_character.getPosition() + startPosition;

    m_addMapObjectFunc(
            std::make_unique<Projectile>(30,
                                         startPosition,
                                         3,
                                         0.6,
                                         power,
                                         m_map,
                                         m_bombHandler));
    // todo: magic numbers? 30, 3, 0.6 ?
    die();
}

void Rifle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_texture, states);
}

void Rifle::update(const sf::Time &deltaTime)
{
    m_texture.setPosition(m_character.getPosition());
}
