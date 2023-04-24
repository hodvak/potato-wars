#include <iostream>
#include <SFML\Graphics.hpp>
#include "ball.h"
#include "moving_map_object.h"
#include "BombHandler.h"
#include "camera.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
    window.setFramerateLimit(60);
    float fps;
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    //sf::View view(sf::FloatRect(0, 0, 1080, 720));
    Camera camera;

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
                                    event.mouseButton.x,
                                    event.mouseButton.y),
                            &image, &bombHandler));
                    camera.setToFolow(balls.back().get());

                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    bombHandler.addBomb(Bomb{MapVector(
                            event.mouseButton.x,
                            event.mouseButton.y),
                                             50,
                                             70000});
                }
            }

        }
        window.clear();
        camera.update(&window);

        float time = clock.restart().asSeconds();
        texture.loadFromImage(image);
        sf::Sprite sprite(texture);


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
            ball->draw(window, sf::Rect<float>{0, 0, 1080, 720});
        }
        currentTime = clock.getElapsedTime();
        previousTime = currentTime;
        camera.update(&window);
        window.display();
    }


}