#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "HUD.h"

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
		GameDataRef			data_;

		sf::Sprite			backgroundSprite_;

		Pipe*				pipe;
		Land*				land;
		Bird*				bird;
		Flash*				flash;
		HUD*				hud;

		Collision			collision;

		sf::Clock			clock_;

		int					gameState_;

		int					score_;
	};
}