#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.h"

#include "Game.h"

namespace FlappyBird
{ 
	class Bird
	{
	public:
		Bird(GameDataRef data);

		void drawBird();

	private:
		GameDataRef data_;

		sf::Sprite	birdSprite_;
	};
}