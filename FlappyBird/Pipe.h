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
		void spawnScoringPipe();

		void movePipes(float dt);

		void drawPipes();

		void randomizePipeOffset();

		const std::vector<sf::Sprite>& getSprites() const;
		std::vector<sf::Sprite>& getScoringSprites();

	private:
		GameDataRef				data_;

		std::vector<sf::Sprite> pipeSprites_;
		std::vector<sf::Sprite> scoringPipeSprites_;

		int						landHeight_;
		int						pipeSpawnYOffset_;
	};
}