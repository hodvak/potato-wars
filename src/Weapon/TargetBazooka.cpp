#include <numbers>
#include "Weapon/TargetBazooka.h"
#include "MapObject/Missile.h"
#include "MapObject/Character.h"
#include "resources_manager.h"

const float TargetBazooka::MAX_ANGLE_DIFF = 3.f;

// todo: 10 is magic 
TargetBazooka::TargetBazooka(const Character &owner, GameHelperData &gameHelperData) :
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
                  10),
                  m_missile(nullptr)
{

}

void TargetBazooka::handleMousePressed(const MapVector &mousePosition)
{
    if(m_missile)
        return;
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
    
    m_missile = new Missile(startPosition,
                                      getGameHelperData(),
                                      power.getAngle(),
                                      m_character.getColor());
    getGameHelperData().addMapObject(std::unique_ptr<Missile>(m_missile));
}

void TargetBazooka::update(const sf::Time &deltaTime)
{
    if(m_missile)
    {
        if(!m_missile->isAlive())
        {
            m_missile = nullptr;
            die();
            return;
        }
        MapVector direction = getGameHelperData().getMousePositionInMap() - m_missile->getPosition();
        float angle = direction.getAngle();
        float missileAngle = m_missile->getVelocity().getAngle();
        float angleDiff = angle - missileAngle;
        if(angleDiff > std::numbers::pi)
            angleDiff -= std::numbers::pi * 2;
        else if(angleDiff < -std::numbers::pi)
            angleDiff += std::numbers::pi * 2;
        
        
        if(angleDiff > MAX_ANGLE_DIFF * deltaTime.asSeconds())
            m_missile->setAngle(missileAngle + MAX_ANGLE_DIFF * deltaTime.asSeconds());
        else if(angleDiff < -MAX_ANGLE_DIFF * deltaTime.asSeconds())
            m_missile->setAngle(missileAngle - MAX_ANGLE_DIFF * deltaTime.asSeconds());
        else
            m_missile->setAngle(angle);
    }
    m_texture.setPosition(m_character.getPosition());
    m_texture.setAimPosition(getGameHelperData().getMousePositionInMap());
}

void TargetBazooka::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_texture, states);
}
