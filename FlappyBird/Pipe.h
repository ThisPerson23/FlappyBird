#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

#include <vector>

namespace FlappyBird
{ 
	class Pipe
	{
	public:
		Pipe(GameDataRef data);

		void drawPipes();

	private:
		GameDataRef				data_;

		std::vector<sf::Sprite> pipeSprites_;
	};
}