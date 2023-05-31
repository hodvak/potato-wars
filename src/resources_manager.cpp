#include "texture_manager.h"

std::map<std::string, sf::Texture*> textures;
std::map<std::string, sf::Font*> fonts;

const sf::Texture* texture_manager::getTexture(const std::string &path)
{
    if (textures.find(path) == textures.end())
    {
        textures[path] = new sf::Texture();
        textures[path]->loadFromFile(path);
    }
    return textures[path];
}

const sf::Font* texture_manager::getFont(const std::string &path)
{
    if (fonts.find(path) == fonts.end())
    {
        fonts[path] = new sf::Font();
        fonts[path]->loadFromFile(path);
    }
    return fonts[path];
}
    