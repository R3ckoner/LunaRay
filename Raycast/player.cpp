#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

constexpr float PI = 3.14159265f;
constexpr float TURN_SPEED = 120.0f;
constexpr float MOVE_SPEED = 100.0f;
void Player::draw(sf::RenderTarget& target) {
	sf::CircleShape circle(8.0f);
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));  // Fix for E0415 and E0140
	circle.setPosition(position);
	circle.setFillColor(sf::Color::Blue);

	sf::RectangleShape line(sf::Vector2f(24.0f, 2.0f));
	line.setPosition(position);
	line.setRotation(angle);
	line.setFillColor(sf::Color::Blue);

	target.draw(line);
	target.draw(circle);

}
void Player::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        angle -= sf::degrees(TURN_SPEED * dt);  // Rotate left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        angle += sf::degrees(TURN_SPEED * dt);  // Rotate right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        float radians = angle.asRadians();  // Get radians for movement
        position.x += cos(radians) * MOVE_SPEED * dt;
        position.y += sin(radians) * MOVE_SPEED * dt;
    }

}

