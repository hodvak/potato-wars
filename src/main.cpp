#include <iostream>
#include "Map.h"
#include <SFML\Graphics.hpp>
#include "ball.h"

void drow_circle(sf::Image &i, sf::Vector2f pos,sf::Color c);

bool check_collision(sf::Image &i, sf::Vector2i pos);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
    window.setFramerateLimit(60);
    sf::Image image;
    image.loadFromFile("resources/mmap.bmp");
    sf::Texture texture;
    std::vector<std::unique_ptr<Ball>> balls;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    balls.push_back(std::make_unique<Ball>(
                            sf::Vector2f(event.mouseButton.x,
                                         event.mouseButton.y)));

                }
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    drow_circle(image, sf::Vector2f(event.mouseButton.x,
                                                    event.mouseButton.y), sf::Color::White);
                }
            }

        }
        window.clear();


        // drow_circle(image, sf::Vector2i(1080 / 2, 720 / 2));
        texture.loadFromImage(image);

        window.draw(sf::Sprite(texture));
        for (int i = 0; i < balls.size(); ++i)
        {
            balls[i]->draw(window, sf::RenderStates::Default);
        }
        for (int i = 0; i < balls.size(); ++i)
        {
            if (check_collision(image, sf::Vector2i(balls[i]->getPosition().x,
                                                    balls[i]->getPosition().y)))
            {

                drow_circle(image, balls[i]->getPosition(), sf::Color::Black);
                balls.erase(balls.begin() + i);
            }
            else
            {
                balls[i]->move(sf::Vector2i(balls[i]->getPosition().x,
                                            (int)floor(balls[i]->getPosition().y + 3) %
                                            HEIGHT));
            }
        }
        window.display();
    }

}

void drow_circle(sf::Image &i, sf::Vector2f pos,sf::Color c)
{
    for (int x = 0; x < 1080; x++)
    {
        for (int y = 0; y < 720; y++)
        {
            if ((x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y) < 1000)
            {
                i.setPixel(x, y, c);
            }
        }
    }
}

bool check_collision(sf::Image &i, sf::Vector2i pos)
{
    if (i.getPixel(pos.x, pos.y) == sf::Color::White)
    {
        return true;
    }
    else
    {
        return false;
    }
}