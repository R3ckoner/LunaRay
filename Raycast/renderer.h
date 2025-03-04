#ifndef _RENDERER_H
#define _RENDERER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "Map.h"

class Renderer

{
public:
	void drawRays(sf::RenderTarget& target, const Player &player, const Map &map);

private:
};
#endif // !_RENDERER_H
