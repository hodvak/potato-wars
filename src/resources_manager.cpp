#include "resources_manager.h"

std::map<std::string, sf::Texture*> textures;
std::map<std::string, sf::Font*> fonts;
std::map<std::string, sf::Image*> images;

const sf::Texture* resources_manager::getTexture(const std::string &path)
{
    if (textures.find(path) == textures.end())
    {
        textures[path] = new sf::Texture();
        textures[path]->loadFromFile(path);
    }
    return textures[path];
}

const sf::Font* resources_manager::getFont(const std::string &path)
{
    if (fonts.find(path) == fonts.end())
    {
        fonts[path] = new sf::Font();
        fonts[path]->loadFromFile(path);
    }
    return fonts[path];
}

const sf::Image* resources_manager::getImage(const std::string &path)
{
    if (images.find(path) == images.end())
    {
        images[path] = new sf::Image();
        images[path]->loadFromFile(path);
    }
    return images[path];
}
    