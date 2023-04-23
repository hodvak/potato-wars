#include <iostream>
#include <SFML\Graphics.hpp>
#include "ball.h"
#include "moving_map_object.h"
#include "BombHandler.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
    window.setFramerateLimit(60);
    float fps;
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    float scale = 2;
    sf::IntRect rect(0, (int) (720 / 2 - 720 / (2 * scale)),
                     (int) (1080 / scale), int(720 / scale));
    sf::Image image;
    image.loadFromFile("resources/mmap.bmp");
    sf::Texture texture;
    std::vector<std::unique_ptr<MovingMapObject>> balls;

    BombHandler bombHandler;
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
                            sf::Vector2f(
                                    event.mouseButton.x/scale + rect.left,
                                    event.mouseButton.y/scale + rect.top),
                            &image, &bombHandler));
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
//                    if(scale == 2)
//                    {
//                        scale = 1;
//                        rect = sf::IntRect(0, 0, 1080, 720);
//                    }
//                    else
//                    {
//                        scale = 2;
//                        rect = sf::IntRect(0, (int)(720/2 - 720/(2 * scale)),(int)(1080/scale), int(720/scale));
//                    }
//                }
                    bombHandler.addBomb(Bomb{MapVector(
                            event.mouseButton.x / scale + rect.left,
                            event.mouseButton.y / scale + rect.top),
                                             50,
                                             70000});
                }
            }

        }
        window.clear();


        float time = clock.restart().asSeconds();
        texture.loadFromImage(image);
        sf::Sprite sprite(texture, rect);
        sprite.setScale(scale, scale);

        window.draw(sprite);

        for (int i = 0; i < balls.size(); ++i)
        {
            balls[i]->update(time, image);
            if (!balls[i]->is_alive())
            {
                balls.erase(balls.begin() + i);
                --i;
            }
        }
        for (auto &ball1: balls)
        {
            for (auto &ball2: balls)
            {
                if (ball1 == ball2)
                {
                    break;
                }
                float distance = sqrt(
                        (ball1->get_position().x - ball2->get_position().x) *
                        (ball1->get_position().x - ball2->get_position().x) +
                        (ball1->get_position().y - ball2->get_position().y) *
                        (ball1->get_position().y - ball2->get_position().y));
                if (distance < ball1->get_radius() + ball2->get_radius())
                {
                    if (!ball1->collide(ball2.get()))
                    {
                        ball2->collide(ball1.get());
                    }
                }
            }
        }
        bombHandler.update(image, balls);
        for (auto &ball: balls)
        {
            ball->draw(window, {(float)rect.left, (float)rect.top, (float)rect.width, (float)rect.height});
        }
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() -
                      previousTime.asSeconds()); // the asSeconds returns a float
//        std::cout << "fps =" << floor(fps)
//                  << std::endl; // flooring it will make the frame rate a rounded number
        previousTime = currentTime;

        window.display();
    }


}