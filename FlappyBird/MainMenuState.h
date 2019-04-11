#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Game.h"

namespace FlappyBird
{ 
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		GameDataRef data_;

		sf::Sprite	backgroundSprite_;
		sf::Sprite	titleSprite_;
		sf::Sprite	playButtonSprite_;
		sf::Sprite  muteMusicButtonSprite_;

		sf::Music	gameTune_;
	};
}