#include "ParallaxLayer.h"
#include "MapVector.h"

ParallaxLayer::ParallaxLayer(const sf::Texture &texture,
                             const sf::FloatRect &mapRect,
                             float speed) :
        m_texture(texture),
        m_speed(speed),
        m_mapRect(mapRect)
{

}

void
ParallaxLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setOrigin((float) m_texture.getSize().x / 2.0f,
                     (float) m_texture.getSize().y / 2.0f);
    
    
    sprite.setScale(m_mapRect.width / (float) m_texture.getSize().x,
                    m_mapRect.height / (float) m_texture.getSize().y);
    
    MapVector center = {m_mapRect.width / 2.0f + m_mapRect.left, m_mapRect.height / 2.0f + m_mapRect.top};
    
    
    MapVector camera = target.getView().getCenter();
    MapVector offset = camera - center;
    offset *= -m_speed;
    sprite.setPosition(center + 
                       offset );
    target.draw(sprite, states);
}
