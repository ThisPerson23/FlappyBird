#include <sstream>
#include <iostream>

#include "GameOverState.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{
	GameOverState::GameOverState(GameDataRef data)
		: data_(data)
	{}

	void GameOverState::init()
	{
		std::cout << "Game Over State" << std::endl;

		data_->assets.loadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		backgroundSprite_.setTexture(this->data_->assets.getTexture("Game Over Background"));
	}

	void GameOverState::handleInput()
	{
		sf::Event event;

		while (data_->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				data_->window.close();
			}
		}
	}

	void GameOverState::update(float dt)
	{}

	void GameOverState::draw(float dt)
	{
		data_->window.clear();
		data_->window.draw(backgroundSprite_);
		data_->window.display();
	}
}