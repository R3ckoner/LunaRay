#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Map.H"


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 450 }), "Raycaster");

	Map map(32.0f, 20, 20);

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
