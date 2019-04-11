#include <sstream>
#include <iostream>

#include "MainMenuState.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{
	MainMenuState::MainMenuState(GameDataRef data)
		: data_(data)
	{}

	void MainMenuState::init()
	{
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
				std::cout << "Go To Game Screen" << std::endl;
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
		data_->window.display();
	}
}