#include <sstream>
#include <iostream>

#include "MainMenuState.h"
#include "GameState.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{
	MainMenuState::MainMenuState(GameDataRef data)
		: data_(data)
	{}

	void MainMenuState::init()
	{
		std::cout << "Main Menu State" << std::endl;

		if (!gameTune_.openFromFile(data_->assets.getMusic("Game Tune")))
		{
			std::cout << "Error Loading Game Tune Music" << std::endl;
		}

		if (!data_->assets.getIsMusicPaused())
		{
			gameTune_.setVolume(10.f);
			gameTune_.setLoop(true);
			gameTune_.play();
		}

		//Background
		data_->assets.loadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		backgroundSprite_.setTexture(this->data_->assets.getTexture("Main Menu Background"));

		//Game Title
		data_->assets.loadTexture("Game Title", GAME_TITLE_FILEPATH);
		titleSprite_.setTexture(this->data_->assets.getTexture("Game Title"));
		titleSprite_.setPosition((SCREEN_WIDTH / 2) - (titleSprite_.getGlobalBounds().width / 2), 
													   titleSprite_.getGlobalBounds().height / 2);

		//Play Button
		data_->assets.loadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		playButtonSprite_.setTexture(this->data_->assets.getTexture("Play Button"));
		playButtonSprite_.setPosition((SCREEN_WIDTH / 2) - (playButtonSprite_.getGlobalBounds().width / 2),
									  (SCREEN_HEIGHT / 2) - (playButtonSprite_.getGlobalBounds().height / 2));

		//Mute Music Button
		data_->assets.loadTexture("Mute Music Button", MUTE_MUSIC_BUTTON_FILEPATH);
		muteMusicButtonSprite_.setTexture(this->data_->assets.getTexture("Mute Music Button"));
		muteMusicButtonSprite_.setPosition(data_->window.getSize().x - muteMusicButtonSprite_.getGlobalBounds().width, data_->window.getSize().y - muteMusicButtonSprite_.getGlobalBounds().height);
	}

	void MainMenuState::handleInput()
	{
		sf::Event event;

		while (data_->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				data_->window.close();
			}

			if (data_->input.isSpriteClicked(playButtonSprite_, sf::Mouse::Left, data_->window))
			{
				std::cout << "Main Menu Play Button Clicked" << std::endl;

				if (!data_->assets.getIsMusicPaused())
				{ 
					gameTune_.stop();
				}

				data_->machine.addState(StateRef(new GameState(data_)), true);
			}

			if (data_->input.isSpriteClicked(muteMusicButtonSprite_, sf::Mouse::Left, data_->window))
			{
				std::cout << "Mute Music Button Clicked" << std::endl;

				if (!data_->assets.getIsMusicPaused())
				{
					data_->assets.setIsMusicPaused(true);
					gameTune_.stop();
				}
				else
				{
					data_->assets.setIsMusicPaused(false);
					gameTune_.play();
					gameTune_.setVolume(10.f);
					gameTune_.setLoop(true);
				}
			}
		}
	}

	void MainMenuState::update(float dt)
	{}

	void MainMenuState::draw(float dt)
	{
		data_->window.clear();
		data_->window.draw(backgroundSprite_);
		data_->window.draw(titleSprite_);
		data_->window.draw(playButtonSprite_);
		data_->window.draw(muteMusicButtonSprite_);
		data_->window.display();
	}
}