#include "renderer.h"
#include <SFML/System.hpp>
#include <cmath>
#include <cstddef>
#include "Map.h"
#include "player.h"
#include <SFML/Graphics.hpp>

constexpr float PI = 3.14159265f;
constexpr size_t MAX_RAYCASTING_DEPTH = 16;

void Renderer::drawRays(sf::RenderTarget& target, const Player& player, const Map& map) {
    float angle = player.angle.asDegrees() * PI / 180.0f;
    float aTan = -1.0f / tan(angle);
	float vTan = -tan(angle);
    float cellSize = map.getCellSize();

    sf::Vector2f rayPos, offset;
    if (cos(angle) > 0.001f) {
        rayPos.x = std::floor(player.position.x / cellSize) * cellSize + cellSize;
        rayPos.y = (player.position.x - rayPos.x) * vTan + player.position.y;

        offset.x = cellSize;
        offset.y = -offset.x * vTan;
    }
    else if (cos(angle) < -0.001f) {
        rayPos.x = std::floor(player.position.x / cellSize) * cellSize;
        rayPos.y = (player.position.x - rayPos.x) * vTan + player.position.y;

        offset.y = -cellSize;
        offset.x = -offset.x * vTan;
    }
    else {
        return;
    }

    const auto& grid = map.getGrid();
    for (size_t i = 0; i < MAX_RAYCASTING_DEPTH; i++) {
        int mapX = (int)(rayPos.x / cellSize);
        int mapY = (int)(rayPos.y / cellSize);

        if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX]) {
            break;
        }

        rayPos += offset;
    }

    sf::Vertex line[2];
    line[0].position = sf::Vector2f(player.position.x, player.position.y);
    line[0].color = sf::Color::Red;

    line[1].position = sf::Vector2f(rayPos.x, rayPos.y);
    line[1].color = sf::Color::Red;

    target.draw(line, 2, sf::PrimitiveType::Lines);
	return;

    if (sin(angle) > 0.001f) {
        rayPos.y = std::floor(player.position.y / cellSize) * cellSize + cellSize;
        rayPos.x = (player.position.y - rayPos.y) * aTan + player.position.x;

        offset.y = cellSize;
        offset.x = -offset.y * aTan;
    }
    else if (sin(angle) < -0.001f) {
        rayPos.y = std::floor(player.position.y / cellSize) * cellSize;
        rayPos.x = (player.position.y - rayPos.y) * aTan + player.position.x;

        offset.y = cellSize;
        offset.x = -offset.y * aTan;
    }
    else {
        return;
    }
}
