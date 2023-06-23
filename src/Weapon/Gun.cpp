#include "Weapon/Gun.h"
#include "MapObject/Projectile.h"
#include "resources_manager.h"

Gun::Gun(const Character &owner,
         const std::function<void(std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
         const GameMap &map,
         BombHandler &bombHandler,
         const std::string &texturePath, 
         const sf::Vector2u &rectTextureSize):
        m_character(owner),
        m_addMapObjectFunc(addMapObjectFunc),
        m_map(map),
        m_bombHandler(bombHandler),
        m_texture(owner.getPosition(),
                  1.5f* owner.getRadius(),
                  resources_manager::get<sf::Texture>(texturePath),
                  sf::IntRect(owner.getColor() * rectTextureSize.x,
                              0,
                              rectTextureSize.x,
                              rectTextureSize.y),
                  {0,0},
                  20)
{
    

}

void Gun::handleMouseMoved(const MapVector &mousePosition)
{
    m_texture.setAimPosition(mousePosition);
}

void Gun::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_texture, states);
}

void Gun::update(const sf::Time &deltaTime)
{
    m_texture.setPosition(m_character.getPosition());
}

void Gun::shot(const MapVector &power, float damage, float weight, float radius)
{
    MapVector startPosition = power;
    
    // +1 to avoid collision with character. 
    // the number can be changed to lower value greater than 0
    startPosition.normalize(m_character.getRadius() + radius + 1);
    
    startPosition += m_character.getPosition();

    m_addMapObjectFunc(
            std::make_unique<Projectile>(weight,
                                         startPosition,
                                         radius,
                                         damage,
                                         power,
                                         m_map,
                                         m_bombHandler)
                                         );
}
