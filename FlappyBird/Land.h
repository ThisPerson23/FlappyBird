#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

#include <vector>

namespace FlappyBird
{ 
	class Land
	{
	public:
		Land(GameDataRef data);
		
		void moveLand(float dt);

		void drawLand();

	private:
		GameDataRef				data_;

		std::vector<sf::Sprite> landSprites_;
	};
}