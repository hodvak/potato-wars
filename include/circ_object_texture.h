#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

/**
 * @brief The CircObjectTexture class is a lazy loader for textures for circles
 * objects in the game, in
 */
class CircObjectTexture
{
public:
    static const CircObjectTexture *getCirc(const std::string &name);
    sf::String getSprite(float seconds, float radius) const;
    
private:
    static std::map<std::string, CircObjectTexture> m_staticObjectTextures;
    CircObjectTexture(const std::string &file_name);
    sf::Texture m_textures;
    float m_texture_radius;
    double time_animation;
};