#ifndef _PLAYER_H
#define _PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player {
public:
	Player();
	void draw(sf::RenderTarget& target);
	void update(float dt);	

	sf::Vector2f position;
	sf::Angle angle;
};
#endif

