#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

constexpr sf::Angle TURN_SPEED = sf::degrees(120.0f);  // Now properly sf::Angle
constexpr float MOVE_SPEED = 100.0f;  // Corrected to float

// Define the constructor to initialize angle
Player::Player() : angle(sf::degrees(0.0f)) {}

void Player::draw(sf::RenderTarget& target) {
    sf::CircleShape circle(8.0f);
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
    circle.setPosition(position);
    circle.setFillColor(sf::Color::Blue);

    sf::RectangleShape line(sf::Vector2f(24.0f, 2.0f));
    line.setPosition(position);
    line.setRotation(angle);  // Fixed error by using asDegrees()
    line.setFillColor(sf::Color::Blue);

    target.draw(line);
    target.draw(circle);
}

void Player::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        angle -= TURN_SPEED * dt;  // SFML 3 supports sf::Angle arithmetic
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        angle += TURN_SPEED * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        float radians = angle.asRadians();  // Convert sf::Angle to radians
        position.x += std::cos(radians) * MOVE_SPEED * dt;
        position.y += std::sin(radians) * MOVE_SPEED * dt;
    }
}
