#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{ 
	class HUD
	{
	public:
		HUD(GameDataRef data);

		void draw();
		void updateScore(int score);

	private:
		GameDataRef data_;

		sf::Text	scoreText_;
	};
}