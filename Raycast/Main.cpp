#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Map.h"
#include "player.h"
#include "renderer.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1200, 675 }), "Raycaster");


    std::vector<std::vector<int>> grid = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	Map map(48.0f, grid);

    Player player;
	player.position =  sf::Vector2f(50, 50);

    Renderer renderer;

    sf::Clock gameClock;
    

    while (window.isOpen()) {
		float dt = gameClock.restart().asSeconds();
        while (auto event = window.pollEvent()) {  // 
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
		player.update(dt);

        window.clear();
		map.draw(window);
		renderer.drawRays(window, player, map);
		player.draw(window);
        window.display();
    }

    return 0;
}
