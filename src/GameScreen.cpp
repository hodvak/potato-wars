#include "GameScreen.h"
#include "GameMap.h"
#include "Camera.h"
#include "Ball.h"
#include <vector>
#include <memory>

static const float PI = acos(-1.0f);

GameScreen::GameScreen()
{
}

std::unique_ptr<Screen> GameScreen::run(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(GameMap::WIDTH, GameMap::HEIGHT), "SFML works!");
    window.setFramerateLimit(60);

    Camera camera;
    sf::Image mask, sky, ground;
    mask.loadFromFile("resources/map.bmp");
    sky.loadFromFile("resources/sky.bmp");
    ground.loadFromFile("resources/ground.bmp");
    sf::Texture pac;
    pac.loadFromFile("resources/superPacman.png");
    sf::Sprite sprite;
    sf::Texture texture;
    GameMap map(mask, sky, ground);

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
                                    (float) event.mouseButton.x,
                                    (float) event.mouseButton.y),
                            &map, &bombHandler));
                    camera.setToFollow(balls.back().get());

                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    bombHandler.addBomb(Bomb{MapVector(
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
            if (!balls[i]->isAlive())
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
                        (ball1->getPosition().x - ball2->getPosition().x) *
                        (ball1->getPosition().x - ball2->getPosition().x) +
                        (ball1->getPosition().y - ball2->getPosition().y) *
                        (ball1->getPosition().y - ball2->getPosition().y));
                if (distance < ball1->getRadius() + ball2->getRadius())
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
        window.display();
    }
    return nullptr;
}