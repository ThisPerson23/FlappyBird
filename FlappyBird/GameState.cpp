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
		, gameState_(GameStates::eReady)
	{}

	void GameState::init()
	{
		std::cout << "Game State" << std::endl;

		if (!hitSoundBuffer_.loadFromFile(HIT_SOUND_FILEPATH))
		{
			std::cout << "Error loading Hit Sound Effect" << std::endl;
		}

		if (!wingSoundBuffer_.loadFromFile(WING_SOUND_FILEPATH))
		{
			std::cout << "Error loading Wing Sound Effect" << std::endl;
		}

		if (!pointSoundBuffer_.loadFromFile(POINT_SOUND_FILEPATH))
		{
			std::cout << "Error loading Point Sound Effect" << std::endl;
		}

		hitSound_.setBuffer(hitSoundBuffer_);
		hitSound_.setVolume(10.f);
		wingSound_.setBuffer(wingSoundBuffer_);
		wingSound_.setVolume(10.f);
		pointSound_.setBuffer(pointSoundBuffer_);
		pointSound_.setVolume(10.f);

		data_->assets.loadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

		data_->assets.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		data_->assets.loadTexture("Pipe Up", PIPE_UP_FILEPATH);
		data_->assets.loadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		data_->assets.loadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		data_->assets.loadTexture("Land", LAND_FILEPATH);

		data_->assets.loadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		data_->assets.loadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		data_->assets.loadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		data_->assets.loadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);

		pipe = new Pipe(data_);
		land = new Land(data_);
		bird = new Bird(data_);
		flash = new Flash(data_);
		hud = new HUD(data_);

		backgroundSprite_.setTexture(this->data_->assets.getTexture("Game Background"));

		score_ = 0;
		hud->updateScore(score_);
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

					wingSound_.play();
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
				pipe->spawnScoringPipe();

				clock_.restart();
			}

			bird->updateBird(dt);

			std::vector<sf::Sprite> landSprites = land->getSprites();

			for (int i = 0; i < landSprites.size(); i++)
			{
				if (collision.checkSpriteCollision(bird->getSprite(), 0.7f, landSprites.at(i), 1.0f))
				{
					gameState_ = GameStates::eGameOver;

					clock_.restart();

					hitSound_.play();
				}
			}

			std::vector<sf::Sprite> pipeSprites = pipe->getSprites();

			for (int i = 0; i < pipeSprites.size(); i++)
			{
				if (collision.checkSpriteCollision(bird->getSprite(), 0.625f, pipeSprites.at(i), 1.0f))
				{
					gameState_ = GameStates::eGameOver;

					clock_.restart();

					hitSound_.play();
				}
			}

			if (GameStates::ePlaying == gameState_)
			{ 
				std::vector<sf::Sprite>& scoringPipeSprites = pipe->getScoringSprites();

				for (int i = 0; i < scoringPipeSprites.size(); i++)
				{
					if (collision.checkSpriteCollision(bird->getSprite(), 0.625f, scoringPipeSprites.at(i), 1.0f))
					{
						score_++;

						hud->updateScore(score_);

						scoringPipeSprites.erase(scoringPipeSprites.begin() + i);

						pointSound_.play();
					}
				}
			}
		}

		if (GameStates::eGameOver == gameState_)
		{
			flash->show(dt);

			if (clock_.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				data_->machine.addState(StateRef(new GameOverState(data_, score_)), true);
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
		flash->draw();
		hud->draw();
		data_->window.display();
	}
}