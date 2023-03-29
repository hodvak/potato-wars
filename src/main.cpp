#include <iostream>
#include "Map.h"
#include <SFML\Graphics.hpp>
int main()
{
    Map map("map.txt");
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
	window.setFramerateLimit(60);
    sf::Image image(1080,720);
    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		/**sf::RectangleShape shape(sf::Vector2f(3, 3));
        shape.setPosition(1080 / 2, 720 / 2);
		shape.setFillColor(sf::Color::Green);
		window.draw(shape);*/
        
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
				if (map(j, i) == 'E')
				{
					image.setPixel(j, i, sf::Color::Black);
				}
				else if (map(j, i) == '#')
				{
					image.setPixel(j, i, sf::Color::White);
				}
				else if (map(j, i) == 'G')
				{
					image.setPixel(j, i, sf::Color::Green);
				}
				else if (map(j, i) == 'B')
				{
					image.setPixel(j, i, sf::Color::Red);
				}
                
                
            }
        }
        
        window.display();
    }

}
