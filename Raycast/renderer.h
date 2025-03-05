#ifndef _RENDERER_H
#define _RENDERER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "Map.h"

constexpr int SCREEN_W = 1200;
constexpr int SCREEN_H = 675;

class Renderer

{
public:
	void draw3dView(sf::RenderTarget& target, const Player& player, const Map& map);
	void drawRays(sf::RenderTarget& target, const Player &player, const Map &map);

private:
};
#endif // !_RENDERER_H
