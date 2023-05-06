#include "texture_manager.h"

std::map<std::string, sf::Texture*> textures;

const sf::Texture* texture_manager::getTexture(const std::string &path)
{
    if (textures.find(path) == textures.end())
    {
        textures[path] = new sf::Texture();
        textures[path]->loadFromFile(path);
    }
    return textures[path];
}
    