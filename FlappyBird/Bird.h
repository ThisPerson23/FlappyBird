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

		void animateBird(float dt);

		void updateBird(float dt);

		void tap();

	private:
		GameDataRef				 data_;

		sf::Sprite				 birdSprite_;

		std::vector<sf::Texture> animationFrames_;

		unsigned int			 animationIterator_;

		sf::Clock				 clock_;

		sf::Clock				 movementClock_;

		int						 birdState_;
	};
}