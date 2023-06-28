#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
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
    const std::string FONT_CALIBRI_PATH = "resources/Fonts/calibrib.ttf";

    const std::string IMG_SKY_PATH = "resources/Images/MapImages/sky.bmp";
    const std::string IMG_GROUND_PATH = "resources/Images/MapImages/ground.bmp";
    const std::string IMG_GROUND2_PATH = "resources/Images/MapImages/sky2.jpg";

    const std::string IMG_LAYER1_PATH = "resources/Images/MapImages/mountain/Layer1.png";
    const std::string IMG_LAYER2_PATH = "resources/Images/MapImages/mountain/Layer2.png";
    const std::string IMG_LAYER3_PATH = "resources/Images/MapImages/mountain/Layer3.png";
    const std::string IMG_LAYER4_PATH = "resources/Images/MapImages/mountain/Layer4.png";

    const std::string IMG_SUNSET1_PATH  = "resources/Images/MapImages/sunset/1.png";
    const std::string IMG_SUNSET2_PATH  = "resources/Images/MapImages/sunset/2.png";
    const std::string IMG_SUNSET3_PATH  = "resources/Images/MapImages/sunset/3.png";
    const std::string IMG_SUNSET4_PATH  = "resources/Images/MapImages/sunset/4.png";
    const std::string IMG_SUNSET5_PATH  = "resources/Images/MapImages/sunset/5.png";
    const std::string IMG_SUNSET6_PATH  = "resources/Images/MapImages/sunset/6.png";
    const std::string IMG_SUNSET7_PATH  = "resources/Images/MapImages/sunset/7.png";
    const std::string IMG_SUNSET8_PATH  = "resources/Images/MapImages/sunset/8.png";
    const std::string IMG_SUNSET9_PATH  = "resources/Images/MapImages/sunset/9.png";





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
    const std::string IMG_FRAGMENTS_PATH = "resources/Images/Textures/fragments.png";
    // 1 * 5
    // arr[a] is the jump image in the color a (`PlayerColor`) and
    // arr[4] is jump image without color
    const std::string IMG_JUMP_PATH = "resources/Images/Textures/jump.png";
    const sf::Vector2u IMG_JUMP_SIZE = {100, 100};

    const std::string IMG_CRATE_PATH = "resources/Images/Textures/CrateTexture.png";
    const std::string IMG_CRATENP_PATH = "resources/Images/Textures/CrateTextureNP.png";
    const std::string IMG_SLINGSHOT_PATH = "resources/Images/Textures/slingshot.png";
    const std::string IMG_HEALTH_PATH = "resources/images/Textures/health2.png";

    //buttons
    const std::string IMG_BUTTON_NEW_GAME_PATH = "resources/Images/Textures/button_new-game.png";
    const std::string IMG_BUTTON_HELP_PATH = "resources/Images/Textures/button_help.png";
    const std::string IMG_BUTTON_SETTINGS_PATH = "resources/Images/Textures/button_settings.png";
    const std::string IMG_BACKGROUND_MAIN_PATH = "resources/Images/Textures/logo-color.png";
    const std::string IMG_BACKGROUND_END_PATH = "resources/Images/Textures/endGameBackGround.png";
    const std::string IMG_BUTTON_BACK_PATH = "resources/Images/Textures/button_back .png";
    const std::string IMG_BUTTON_LEFT_PATH = "resources/Images/Textures/button_left_arrow.png";
    const std::string IMG_BUTTON_RIGHT_PATH = "resources/Images/Textures/button_right_arrow.png";

    // all the levels will be in the format of:
    // std::format(PATH_LEVELS,int levelNumber) 
    const std::string PATH_LEVELS = "resources/Levels/lvl{}/map.bmp";

    //sounds
    const std::string SOUND_WEAPONCHOOSE_PATH = "resources/Sounds/weaponChoosing.wav";
    const std::string SOUND_SNIPERSHOT_PATH = "resources/Sounds/SniperShhot.wav";
    const std::string SOUND_MINIGUNSHOT_PATH = "resources/Sounds/miniGunShoot.wav";
    const std::string SOUND_PICKCRATE_PATH = "resources/Sounds/pickCrate.wav";
    const std::string SOUND_PICKHEALTH_PATH = "resources/Sounds/HealthUP.wav";
    const std::string SOUND_WEAPONTHROW_PATH = "resources/Sounds/WeapenThrow.wav";
    const std::string SOUND_ROCKBOUNCE_PATH = "resources/Sounds/rockBounce.wav";
    const std::string SOUND_CAMERASWITCH_PATH = "resources/Sounds/CameraPan.wav";
    const std::string SOUND_CRATEIMPACT_PATH = "resources/Sounds/CrateImpact.wav";
    const std::string SOUND_BOMBEXPLOSION_PATH = "resources/Sounds/Explosion2.wav";



    template<class T>
    const T &get(const std::string &path)
    {
        static std::unordered_map<std::string, T> resources;
        if (resources.find(path) == resources.end())
        {
            resources.try_emplace(path);
            resources[path].loadFromFile(path);
        }
        return resources[path];
    }


}