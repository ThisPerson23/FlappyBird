#include <sstream>
#include <iostream>

#include "GameState.h"
#include "GameOverState.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{
	GameState::GameState(GameDataRef data)
		: data_(data)
	{}

	void GameState::init()
	{
		std::cout << "Game State" << std::endl;

		data_->assets.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		backgroundSprite_.setTexture(this->data_->assets.getTexture("Game Background"));

		pipe = new Pipe(data_);

		data_->assets.loadTexture("Pipe Up", PIPE_UP_FILEPATH);
		data_->assets.loadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
	}

	void GameState::handleInput()
	{
		sf::Event event;

		while (data_->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				data_->window.close();
			}

			if (data_->input.isSpriteClicked(backgroundSprite_, sf::Mouse::Left, data_->window))
			{
				std::cout << "Background In Game State Clicked" << std::endl;
				std::cout << "Pipe Spawned" << std::endl;
				pipe->spawnInvisiblePipe();
				pipe->spawnBottomPipe();
				pipe->spawnTopPipe();
			}
		}
	}

	void GameState::update(float dt)
	{
		pipe->movePipes(dt);
	}

	void GameState::draw(float dt)
	{
		data_->window.clear();
		data_->window.draw(backgroundSprite_);
		pipe->drawPipes();
		data_->window.display();
	}
}