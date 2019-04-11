#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.h"

#include "Game.h"

#include <vector>

namespace FlappyBird
{ 
	class Bird
	{
	public:
		Bird(GameDataRef data);

		void drawBird();

		void animate(float dt);

	private:
		GameDataRef				 data_;

		sf::Sprite				 birdSprite_;

		std::vector<sf::Texture> animationFrames_;

		unsigned int			 animationIterator_;

		sf::Clock				 clock_;
	};
}