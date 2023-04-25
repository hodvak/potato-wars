#include <iostream>
#include <SFML\Graphics.hpp>
#include "ball.h"
#include "moving_map_object.h"
#include "BombHandler.h"
#include "camera.h"
#include "Map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(Map::WIDTH, Map::HEIGHT), "SFML works!");
    window.setFramerateLimit(60);
    float fps;
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
                                    event.mouseButton.x,
                                    event.mouseButton.y),
                            &map, &bombHandler));
                    camera.setToFollow(balls.back().get());

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

        texture.loadFromImage(*map.getDisplay());
        sprite.setTexture(texture);
        window.draw(sprite);


        float time = clock.restart().asSeconds();




        for (int i = 0; i < balls.size(); ++i)
        {
            balls[i]->update(time, &map);
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
            ball->draw(window, sf::Rect<float>{0, 0, Map::WIDTH, Map::HEIGHT});
        }
        currentTime = clock.getElapsedTime();
        previousTime = currentTime;
        window.display();
    }


}
sf::Image blendImages(sf::Image mask, sf::Image sky, sf::Image ground)
{
    // Get the dimensions of the images
    unsigned int width = mask.getSize().x;
    unsigned int height = mask.getSize().y;

    // Create a new image to store the blended result
    sf::Image blendedImage;
    blendedImage.create(width, height);

    // Loop through each pixel of the mask image
    for(unsigned int x = 0; x < width; x++)
    {
        for(unsigned int y = 0; y < height; y++)
        {
            // Get the color of the pixel in the mask image
            sf::Color maskColor = mask.getPixel(x, y);

            // Get the color of the corresponding pixels in the sky and ground images
            sf::Color skyColor = sky.getPixel(x, y);
            sf::Color groundColor = ground.getPixel(x, y);

            // Calculate the weight of each color based on the mask color
            float weight = (float)maskColor.r / 255.0f;

            // Interpolate the sky and ground colors based on the weight
            sf::Color blendedColor = sf::Color(
                    (1.0f - weight) * skyColor.r + weight * groundColor.r,
                    (1.0f - weight) * skyColor.g + weight * groundColor.g,
                    (1.0f - weight) * skyColor.b + weight * groundColor.b,
                    255 // Set the alpha to 255 (fully opaque)
            );

            // Set the blended color for the pixel in the blended image
            blendedImage.setPixel(x, y, blendedColor);
        }
    }

    // Return the blended image
    return blendedImage;
}
//
//int main(){
//    sf::Image map, ground, sky;
//    map.loadFromFile("resources/mmap.bmp");
//    ground.loadFromFile("resources/ground.bmp");
//    sky.loadFromFile("resources/sky.bmp");
//
//    sf::Image blendedImage = blendImages(map, sky, ground);
//
//// Display the blended image using an sf::Texture and sf::Sprite
//    sf::Texture blendedTexture;
//    blendedTexture.loadFromImage(blendedImage);
//
//    sf::Sprite blendedSprite;
//    blendedSprite.setTexture(blendedTexture);
//
//// Draw the sprite to an sf::RenderWindow object
//    sf::RenderWindow window(sf::VideoMode(WIDTH,HiGHT), "Blended Image");
//    window.draw(blendedSprite);
//    window.display();
//
//// Wait for the window to close
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//    }
//
//}