#pragma once

#include <SFML/Graphics.hpp>

/**
 * a class that manages the textures in the game.
 * load the textures when needed and return them when asked.
 */
namespace resources_manager
{
    /**
     * get a texture from the manager.
     * if the texture is not loaded, load it.
     * @param path the path to the texture
     * @return the texture
     */
    const sf::Texture *getTexture(const std::string &path);

    /**
     * get a font from the manager.
     * if the font is not loaded, load it.
     * @param path the path to the font
     * @return the font
     */
    const sf::Font *getFont(const std::string &path);

    /**
     * get an image from the manager.
     * if the image is not loaded, load it.
     * @param path the path to the image
     * @return the image
     */
    const sf::Image *getImage(const std::string &path);

    /**
     * consts for the resources
     * ======= IMAGE =======
     * every const that start with IMG_ is the path to the texture
     * * every const that ends with _PATH is the path to the resource
     * * every const that ends with _SIZE is the rect for specific texture
     *   for those consts there will be an explanation about the texture rect
     *   indexes. size of the matrix, Y * X then explanation about the indexes
     *   in the matrix
     * 
     * ======= FONTS =======
     * every const that start with FONT_ is the path to the font
     * * every const that ends with _PATH is the path to the resource
     * 
     * ======= PATHS =======
     * paths to resources by groups
     */

    const std::string FONT_ARCADE_PATH = "resources/Fonts/ARCADE2.otf";

    const std::string IMG_SKY_PATH = "resources/Images/MapImages/sky.bmp";
    const std::string IMG_GROUND_PATH = "resources/Images/MapImages/ground.bmp";


    // 1 * 4
    // arr[a] is the player in the color a (`PlayerColor`)
    const std::string IMG_PLAYER_PATH = "resources/Images/Textures/players.png";
    const sf::Vector2u IMG_PLAYER_SIZE = {100, 100};

    const std::string IMG_AIM_PATH = "resources/Images/Textures/Aim.png";

    const std::string IMG_BOMB_PATH = "resources/Images/Textures/BOMB.png";

    // 1 * 5
    // arr[a] is the rifle in the color a (`PlayerColor`) and 
    // arr[4] is rifle without color
    const std::string IMG_RIFLE_PATH = "resources/Images/Textures/rifles.png";
    const sf::Vector2u IMG_RIFLE_SIZE = {100, 100};

    // 1 * 5
    // arr[a] is the shotgun in the color a (`PlayerColor`) and 
    // arr[4] is shotgun without color
    const std::string IMG_SHOTGUN_PATH = "resources/Images/Textures/shotgun.png";
    const sf::Vector2u IMG_SHOTGUN_SIZE = {100, 100};


    // 1 * 5
    // arr[a] is the shotgun in the color a (`PlayerColor`) and 
    // arr[4] is shotgun without color
    const std::string IMG_MINIGUN_PATH = "resources/Images/Textures/minigun.png";
    const sf::Vector2u IMG_MINIGUN_SIZE = {200, 200};

    // 3 * 5
    // arr[y][x] is the rock in the:
    // color x (`PlayerColor`) and arr[y][4] is rock without color
    // damage y (the arr[0][x] is the rock that was not damaged at all)
    const std::string IMG_ROCK_PATH = "resources/Images/Textures/rocks.png";
    const sf::Vector2u IMG_ROCK_SIZE = {100, 100};

    // 1 * 5
    // arr[a] is the jump image in the color a (`PlayerColor`) and
    // arr[4] is jump image without color
    const std::string IMG_JUMP_PATH = "resources/Images/Textures/jump.png";
    const sf::Vector2u IMG_JUMP_SIZE = {100, 100};


    const std::string IMG_SLINGSHOT_PATH = "resources/Images/Textures/slingshot.png";

    // all the levels will be in the format of:
    // PATH_LEVELS + "lvl" + level_number + "/map.bmp"
    const std::string PATH_LEVELS = "resources/Levels/";

}