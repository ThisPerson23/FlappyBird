#include <sstream>
#include <iostream>

#include "SplashState.h"
#include "MainMenuState.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{
	SplashState::SplashState(GameDataRef data)
		: data_(data)
	{}

	void SplashState::init()
	{
		std::cout << "Splash Screen State" << std::endl;

		data_->assets.loadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		backgroundSprite_.setTexture(this->data_->assets.getTexture("Splash State Background"));
	}

	void SplashState::handleInput()
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

	void SplashState::update(float dt)
	{
		if (clock_.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			data_->machine.addState(StateRef(new MainMenuState(data_)), true);
		}
	}

	void SplashState::draw(float dt)
	{
		data_->window.clear();
		data_->window.draw(backgroundSprite_);
		data_->window.display();
	}
}