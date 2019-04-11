#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "DEFINITIONS.h"

#include <vector>

namespace FlappyBird
{ 
	class Pipe
	{
	public:
		Pipe(GameDataRef data);

		void spawnBottomPipe();
		void spawnTopPipe();
		void spawnInvisiblePipe();

		void movePipes(float dt);

		void drawPipes();

	private:
		GameDataRef				data_;

		std::vector<sf::Sprite> pipeSprites_;
	};
}