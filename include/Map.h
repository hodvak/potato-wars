#pragma once

#include <SFML/Graphics.hpp>
#include "MapVector.h"

class Map
{
public:

    static const int WIDTH = 1080;
    static const int HEIGHT = 720;

    Map(sf::Image mask, sf::Image sky, sf::Image ground) :
            m_mask(mask),
            m_sky(sky),
            m_ground(ground)
    {
        m_display.create(WIDTH, HEIGHT);
        for (int i = 0; i < WIDTH; ++i)
        {
            for (int j = 0; j < HEIGHT; ++j)
            {
                sf::Color maskColor = mask.getPixel(i, j);
                sf::Color skyColor = sky.getPixel(i, j);
                sf::Color groundColor = ground.getPixel(i, j);
                if (maskColor == sf::Color::Black)
                {
                    m_display.setPixel(i, j, skyColor);
                }
                else
                {
                    m_display.setPixel(i, j, groundColor);
                }
            }

        }
    }

    sf::Color getSkyColor(int x, int y)
    {
        return m_sky.getPixel(x, y);
    }

    sf::Color getGroundColor(int x, int y)
    {
        return m_ground.getPixel(x, y);
    }

    sf::Color getMaskColor(int x, int y)
    {
        return m_mask.getPixel(x, y);
    }

    sf::Image *getMask()
    {
        return &m_mask;
    }

    sf::Image *getSky()
    {
        return &m_sky;
    }

    sf::Image *getGround()
    {
        return &m_ground;
    }

    sf::Image *getDisplay()
    {
        return &m_display;
    }

    void drawCircle(MapVector pos, int radius)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            for (int j = 0; j < HEIGHT; ++j)
            {
                if ((pos-MapVector(i,j)).getMagnitude() < radius)
                {
                    m_mask.setPixel(i, j, sf::Color::Black);
                    m_display.setPixel(i, j, getSkyColor(i, j));
                }
            }
        }
    }

private:
    sf::Image m_mask;
    sf::Image m_sky;
    sf::Image m_ground;
    sf::Image m_display;
};