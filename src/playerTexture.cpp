#include "player_texture.h"
#include "texture_manager.h"

PlayerTexture::PlayerTexture(PlayerColor color, float radius)
{
    m_sprite.setTexture(*texture_manager::getTexture("resources/players.png"));
    m_sprite.setTextureRect(sf::IntRect(100*(int)color, 0, 
                                        100, 100));
    m_sprite.setScale(radius/50, radius/50);
    m_sprite.setOrigin(50, 50);
}

void PlayerTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}