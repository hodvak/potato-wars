#pragma once

/**
 * an enum for the player color
 * arrange as the players.png file
 */
enum PlayerColor
{
    YELLOW,
    GREEN,
    RED,
    BLUE
};

/**
* get sf::Color from PlayerColor
*/
static sf::Color getColor(PlayerColor color)
{
    switch (color)
    {
    case YELLOW:
        return {255, 255, 0};
    case GREEN:
        return {0, 255, 0};
    case RED:
        return {255, 0, 0};
    case BLUE:
        return {0, 0, 255};
    default:
        return sf::Color::White;
    }
}