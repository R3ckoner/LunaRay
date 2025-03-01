#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Map.H"


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
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {  // 
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
		map.draw(window);
        window.display();
    }

    return 0;
}
