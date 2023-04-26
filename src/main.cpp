#include <iostream>
#include <SFML\Graphics.hpp>
#include "ball.h"
#include "moving_map_object.h"
#include "bomb_handler.h"
#include "camera.h"
#include "map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(Map::WIDTH, Map::HEIGHT), "SFML works!");
    window.setFramerateLimit(60);
    
    Camera camera;
    sf::Image mask, sky, ground;
    mask.loadFromFile("resources/map.bmp");
    sky.loadFromFile("resources/sky.bmp");
    ground.loadFromFile("resources/ground.bmp");
    sf::Sprite sprite;
    sf::Texture texture;
    Map map(mask, sky, ground);

    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
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
                                    (float)event.mouseButton.x,
                                    (float)event.mouseButton.y),
                            &map, &bombHandler));
                    camera.set_to_follow(balls.back().get());

                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    bombHandler.add_bomb(Bomb{MapVector(
                            (float) event.mouseButton.x,
                            (float) event.mouseButton.y),
                                              50,
                                              70000});
                }
            }

        }
        window.clear();
        camera.update(&window);
        window.draw(map);


        float time = clock.restart().asSeconds();




        for (int i = 0; i < balls.size(); ++i)
        {
            balls[i]->update(time);
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
        bombHandler.update(&map, balls);
        for (auto &ball: balls)
        {
            window.draw(*ball);
        }
        currentTime = clock.getElapsedTime();
        previousTime = currentTime;
        window.display();
    }


}