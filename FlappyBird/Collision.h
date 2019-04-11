#pragma once

#include <SFML/Graphics.hpp>

namespace FlappyBird
{ 
	class Collision
	{
	public:
		Collision();

		bool checkSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2);
	};
}