#include "Game.h"
#include "SplashState.h"

namespace FlappyBird
{
	Game::Game(int width, int height, std::string title)
	{
		data_->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

		data_->machine.addState(StateRef(new SplashState(this->data_)));

		this->run();
	}

	void Game::run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->clock_.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->data_->window.isOpen())
		{
			this->data_->machine.processStateChanges();

			newTime = this->clock_.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->data_->machine.getActiveState()->handleInput();
				this->data_->machine.getActiveState()->update(dt);

				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->data_->machine.getActiveState()->draw(interpolation);
		}
	}
}