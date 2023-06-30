#include "Weapon/Bazooka.h"
#include "MapObject/Missile.h"
#include "MapObject/Character.h"
#include "resources_manager.h"


Bazooka::Bazooka(const Character &owner, GameHelperData &gameHelperData) :
        Weapon(gameHelperData),
        m_character(owner),
        m_texture(owner.getPosition(),
                  owner.getRadius() * 2,
                  resources_manager::get<sf::Texture>(
                          resources_manager::IMG_BAZOOKA_PATH),
                  sf::IntRect(owner.getColor() *
                              resources_manager::IMG_BAZOOKA_SIZE.x,
                              0,
                              resources_manager::IMG_BAZOOKA_SIZE.x,
                              resources_manager::IMG_BAZOOKA_SIZE.y),
                  owner.getPosition(),
                  10)
{

}

void Bazooka::handleMousePressed(const MapVector &mousePosition)
{
//    const MapVector &position,
//    GameHelperData &data,
//    float angle,
//    PlayerColor color
    MapVector power = mousePosition - m_character.getPosition();
    MapVector startPosition = power;

    // +1 to avoid collision with character. 
    // the number can be changed to lower value greater than 0
    startPosition.normalize(m_character.getRadius() + Missile::RADIUS + 1);

    startPosition += m_character.getPosition();

    getGameHelperData().addMapObject(
            std::make_unique<Missile>(startPosition,
                                      getGameHelperData(),
                                      power.getAngle(),
                                      m_character.getColor()));
    die();
}

void Bazooka::update(const sf::Time &deltaTime)
{
    m_texture.setPosition(m_character.getPosition());
    m_texture.setAimPosition(getGameHelperData().getMousePositionInMap());
}

void Bazooka::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_texture, states);
}
