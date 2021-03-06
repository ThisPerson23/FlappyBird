#include <sstream>
#include <iostream>
#include <fstream>

#include "GameOverState.h"
#include "GameState.h"
#include "MainMenuState.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{
	GameOverState::GameOverState(GameDataRef data, int score)
		: data_(data)
		, score_(score)
	{}

	void GameOverState::init()
	{
		//Debug
		std::cout << "Game Over State" << std::endl;

		std::ifstream readFile;
		readFile.open(HIGH_SCORES_FILE_PATH);

		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> highScore_;
			}
		}

		readFile.close();

		std::ofstream writeFile(HIGH_SCORES_FILE_PATH);

		if (writeFile.is_open())
		{
			if (score_ > highScore_)
			{
				highScore_ = score_;
			}

			writeFile << highScore_;
		}

		writeFile.close();

		data_->assets.loadFont("Marker Felt", MARKER_FELT_FONT_FILEPATH);

		data_->assets.loadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		data_->assets.loadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		data_->assets.loadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);

		data_->assets.loadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
		data_->assets.loadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
		data_->assets.loadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
		data_->assets.loadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);

		backgroundSprite_.setTexture(this->data_->assets.getTexture("Game Over Background"));
		gameOverTitleSprite_.setTexture(this->data_->assets.getTexture("Game Over Title"));
		gameOverContainerSprite_.setTexture(this->data_->assets.getTexture("Game Over Body"));
		retryButtonSprite_.setTexture(this->data_->assets.getTexture("Play Button"));

		gameOverContainerSprite_.setPosition((data_->window.getSize().x / 2) - (gameOverContainerSprite_.getGlobalBounds().width / 2),
											 (data_->window.getSize().y / 2) - (gameOverContainerSprite_.getGlobalBounds().height / 2));

		gameOverTitleSprite_.setPosition((data_->window.getSize().x / 2) - (gameOverTitleSprite_.getGlobalBounds().width / 2),
										  gameOverContainerSprite_.getPosition().y - (gameOverTitleSprite_.getGlobalBounds().height * 1.2));

		retryButtonSprite_.setPosition((data_->window.getSize().x / 2) - (retryButtonSprite_.getGlobalBounds().width / 2),
										gameOverContainerSprite_.getPosition().y + gameOverContainerSprite_.getGlobalBounds().height + (retryButtonSprite_.getGlobalBounds().height * 0.2));

		returnToMenuText_.setFont(data_->assets.getFont("Marker Felt"));
		returnToMenuText_.setString("Press Escape to Return to Menu");
		returnToMenuText_.setCharacterSize(56);
		returnToMenuText_.setFillColor(sf::Color::White);
		returnToMenuText_.setOrigin(returnToMenuText_.getGlobalBounds().width / 2, returnToMenuText_.getGlobalBounds().height / 2);
		returnToMenuText_.setPosition(data_->window.getSize().x / 2,
			retryButtonSprite_.getPosition().y + retryButtonSprite_.getGlobalBounds().height + (returnToMenuText_.getGlobalBounds().height * 1.2));

		scoreText_.setFont(data_->assets.getFont("Flappy Font"));
		scoreText_.setString(std::to_string(score_));
		scoreText_.setCharacterSize(56);
		scoreText_.setFillColor(sf::Color::White);
		scoreText_.setOrigin(scoreText_.getGlobalBounds().width / 2, scoreText_.getGlobalBounds().height / 2);
		scoreText_.setPosition(data_->window.getSize().x / 10 * 7.25, data_->window.getSize().y / 2.15);

		highScoreText_.setFont(data_->assets.getFont("Flappy Font"));
		highScoreText_.setString(std::to_string(highScore_));
		highScoreText_.setCharacterSize(56);
		highScoreText_.setFillColor(sf::Color::White);
		highScoreText_.setOrigin(highScoreText_.getGlobalBounds().width / 2, highScoreText_.getGlobalBounds().height / 2);
		highScoreText_.setPosition(data_->window.getSize().x / 10 * 7.25, data_->window.getSize().y / 1.78);

		if (score_ >= PLATINUM_MEDAL_SCORE)
		{
			medalSprite_.setTexture(data_->assets.getTexture("Platinum Medal"));
		}
		else if (score_ >= GOLD_MEDAL_SCORE)
		{
			medalSprite_.setTexture(data_->assets.getTexture("Gold Medal"));
		}
		else if (score_ >= SILVER_MEDAL_SCORE)
		{
			medalSprite_.setTexture(data_->assets.getTexture("Silver Medal"));
		}
		else
		{
			medalSprite_.setTexture(data_->assets.getTexture("Bronze Medal"));
		}

		medalSprite_.setPosition(175, 465);
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

			if (data_->input.isSpriteClicked(retryButtonSprite_, sf::Mouse::Left, data_->window))
			{
				data_->machine.addState(StateRef(new GameState(data_)), true);
			}

			if (sf::Event::KeyPressed == event.type && event.key.code == sf::Keyboard::Escape)
			{
				data_->machine.addState(StateRef(new MainMenuState(data_)), true);
			}
		}
	}

	void GameOverState::update(float dt)
	{}

	void GameOverState::draw(float dt)
	{
		data_->window.clear();
		data_->window.draw(backgroundSprite_);
		data_->window.draw(gameOverContainerSprite_);
		data_->window.draw(gameOverTitleSprite_);
		data_->window.draw(retryButtonSprite_);
		data_->window.draw(scoreText_);
		data_->window.draw(highScoreText_);
		data_->window.draw(medalSprite_);
		data_->window.draw(returnToMenuText_);
		data_->window.display();
	}
}