#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game.h"

namespace FlappyBird
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		GameDataRef data_;

		sf::Sprite	backgroundSprite_;

		sf::Sprite	gameOverTitleSprite_;
		sf::Sprite	gameOverContainerSprite_;
		sf::Sprite	retryButtonSprite_;
	};
}