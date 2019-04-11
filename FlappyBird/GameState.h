#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game.h"
#include "Pipe.h"

namespace FlappyBird
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		GameDataRef data_;

		sf::Sprite	backgroundSprite_;

		Pipe* pipe;
	};
}