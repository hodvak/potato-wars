#pragma once

#include <SFML/Graphics.hpp>
#include <map>

/**
 * a class that manages the textures in the game.
 * load the textures when needed and return them when asked.
 */
namespace texture_manager
{
    /**
     * get a texture from the manager.
     * if the texture is not loaded, load it.
     * @param path the path to the texture
     * @return the texture
     */
    const sf::Texture* getTexture(const std::string &path);
}