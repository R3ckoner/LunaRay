#ifndef _PLAYER_H
#define _PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player {
public:
	void draw(sf::RenderTarget& target);
	void update(float dt);	

	sf::Vector2f position;
	float angle;
};
#endif

