#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

constexpr float PI = 3.14159265f;
constexpr float TURN_SPEED = 120.0f;
constexpr float MOVE_SPEED = 100.0f;
void Player::draw(sf::RenderTarget& target) {
	sf::CircleShape circle(5.0f);
	circle.setPosition(position);

	target.draw(circle);

}
void Player::update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		angle -= TURN_SPEED * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		angle += TURN_SPEED * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		float radians = angle * PI / 180.0f;

		position.x += cos(radians) * MOVE_SPEED * dt;
		position.y += sin(radians) * MOVE_SPEED * dt;
	}
}