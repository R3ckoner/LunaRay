#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>

constexpr float PI = 3.141592653589793f;
constexpr float PLAYER_FOV = 60.0f;
constexpr size_t MAX_RAYCAST_DEPTH = 16;
constexpr size_t NUM_RAYS = 120;
constexpr float COLUMN_WIDTH = SCREEN_W / (float)NUM_RAYS;

struct Ray {
    sf::Vector2f hitPosition;
    float distance;
    bool hit;
};

static Ray castRay(sf::Vector2f start, float angleInDegrees, const Map& map);

void Renderer::draw3dView(sf::RenderTarget& target, const Player& player, const Map& map) {
    float playerAngleDegrees = player.angle.asDegrees();
    float angle = playerAngleDegrees - PLAYER_FOV / 2.0f;
    float angleIncrement = PLAYER_FOV / (float)NUM_RAYS;
    for (size_t i = 0; i < NUM_RAYS; i++, angle += angleIncrement) {
        Ray ray = castRay(player.position, angle, map);

        if (ray.hit) {
            float wallHeight = (map.getCellSize() * SCREEN_H) / ray.distance;
			if (wallHeight > SCREEN_H) {
				wallHeight = SCREEN_H;
			}

			float wallOffset = SCREEN_H / 2.0f - wallHeight / 2.0f;

            sf::RectangleShape column(sf::Vector2f(COLUMN_WIDTH, wallHeight));
            column.setPosition(sf::Vector2f(i * COLUMN_WIDTH, wallOffset));
            target.draw(column);

        }
    }
}

void Renderer::drawRays(sf::RenderTarget& target, const Player& player, const Map& map) {
    float playerAngleDegrees = player.angle.asDegrees();

    for (float angle = playerAngleDegrees - PLAYER_FOV / 2.0f;
         angle < playerAngleDegrees + PLAYER_FOV; angle += 0.5f) {

        Ray ray = castRay(player.position, angle, map);

        if (ray.hit) {
            // Use sf::Vertex with sf::Vector2f for position and sf::Color for color
            sf::Vertex line[2];
            line[0].position = sf::Vector2f(player.position.x, player.position.y);
            line[0].color = sf::Color::Red;

            line[1].position = sf::Vector2f(ray.hitPosition);
            line[1].color = sf::Color::Red;

            target.draw(line, 2, sf::PrimitiveType::Lines);
        }
    }
}

Ray castRay(sf::Vector2f start, float angleInDegrees, const Map& map) {
    float angle = angleInDegrees * PI / 180.0f;
    float vtan = -std::tan(angle), htan = -1.0f / std::tan(angle);
    float cellSize = map.getCellSize();

    bool hit = false;
    size_t vdof = 0, hdof = 0;
    float vdist = std::numeric_limits<float>::max();
    float hdist = std::numeric_limits<float>::max();

    sf::Vector2f vRayPos, hRayPos, offset;
    if (std::cos(angle) > 0.001f) {
        vRayPos.x = std::floor(start.x / cellSize) * cellSize + cellSize;
        vRayPos.y = (start.x - vRayPos.x) * vtan + start.y;

        offset.x = cellSize;
        offset.y = -offset.x * vtan;
    }
    else if (std::cos(angle) < -0.001f) {
        vRayPos.x = std::floor(start.x / cellSize) * cellSize - 0.01f;
        vRayPos.y = (start.x - vRayPos.x) * vtan + start.y;

        offset.x = -cellSize;
        offset.y = -offset.x * vtan;
    }
    else {
        vdof = MAX_RAYCAST_DEPTH;
    }

    const auto& grid = map.getGrid();
    for (; vdof < MAX_RAYCAST_DEPTH; vdof++) {
        int mapX = (int)(vRayPos.x / cellSize);
        int mapY = (int)(vRayPos.y / cellSize);

        if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX]) {
            hit = true;
            vdist = std::sqrt((vRayPos.x - start.x) * (vRayPos.x - start.x) +
                (vRayPos.y - start.y) * (vRayPos.y - start.y));
            break;
        }

        vRayPos += offset;
    }

    if (sin(angle) > 0.001f) {
        hRayPos.y = std::floor(start.y / cellSize) * cellSize + cellSize;
        hRayPos.x = (start.y - hRayPos.y) * htan + start.x;

        offset.y = cellSize;
        offset.x = -offset.y * htan;
    }
    else if (sin(angle) < -0.001f) {
        hRayPos.y = std::floor(start.y / cellSize) * cellSize - 0.01f;
        hRayPos.x = (start.y - hRayPos.y) * htan + start.x;

        offset.y = -cellSize;
        offset.x = -offset.y * htan;
    }
    else {
        hdof = MAX_RAYCAST_DEPTH;
    }

    for (; hdof < MAX_RAYCAST_DEPTH; hdof++) {
        int mapX = (int)(hRayPos.x / cellSize);
        int mapY = (int)(hRayPos.y / cellSize);

        if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX]) {
            hit = true;
            hdist = std::sqrt((hRayPos.x - start.x) * (hRayPos.x - start.x) +
                (hRayPos.y - start.y) * (hRayPos.y - start.y));
            break;
        }

        hRayPos += offset;
    }

    return Ray{ hdist < vdist ? hRayPos : vRayPos, std::min(hdist, vdist), hit };
}
