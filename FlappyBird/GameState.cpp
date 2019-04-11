#include <sstream>
#include <iostream>

#include "GameState.h"
#include "GameOverState.h"
#include "MainMenuState.h"

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
		data_->assets.loadTexture("Pipe Up", PIPE_UP_FILEPATH);
		data_->assets.loadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		data_->assets.loadTexture("Land", LAND_FILEPATH);

		data_->assets.loadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		data_->assets.loadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		data_->assets.loadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		data_->assets.loadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);

		pipe = (new Pipe(data_));
		land = (new Land(data_));
		bird = (new Bird(data_));

		backgroundSprite_.setTexture(this->data_->assets.getTexture("Game Background"));

		gameState_ = GameStates::eReady;
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
				if (GameStates::eGameOver != gameState_)
				{ 
					gameState_ = GameStates::ePlaying;
					bird->tap();
				}
			}
		}
	}

	void GameState::update(float dt)
	{
		if (GameStates::eGameOver != gameState_)
		{
			bird->animateBird(dt);
			land->moveLand(dt);
		}

		if (GameStates::ePlaying == gameState_)
		{
			pipe->movePipes(dt);

			if (clock_.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				pipe->randomizePipeOffset();

				pipe->spawnInvisiblePipe();
				pipe->spawnBottomPipe();
				pipe->spawnTopPipe();

				clock_.restart();
			}

			bird->updateBird(dt);

			std::vector<sf::Sprite> landSprites = land->getSprites();

			for (int i = 0; i < landSprites.size(); i++)
			{
				if (collision.checkSpriteCollision(bird->getSprite(), landSprites.at(i)))
				{
					gameState_ = GameStates::eGameOver;
				}
			}
		}
	}

	void GameState::draw(float dt)
	{
		data_->window.clear();
		data_->window.draw(backgroundSprite_);
		pipe->drawPipes();
		land->drawLand();
		bird->drawBird();
		data_->window.display();
	}
}