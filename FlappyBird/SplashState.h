#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game.h"

namespace FlappyBird
{ 
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);
		
		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		GameDataRef data_;

		sf::Clock	clock_;

		sf::Texture backgroundTexture_;
		sf::Sprite	backgroundSprite_;
	};
}