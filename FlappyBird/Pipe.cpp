#include "Pipe.h"

namespace FlappyBird
{
	Pipe::Pipe(GameDataRef data)
		: data_(data)
	{}

	void Pipe::spawnBottomPipe()
	{
		sf::Sprite sprite(data_->assets.getTexture("Pipe Up"));

		sprite.setPosition(data_->window.getSize().x, data_->window.getSize().y - sprite.getGlobalBounds().height);

		pipeSprites_.push_back(sprite);
	}

	void Pipe::spawnTopPipe()
	{
		sf::Sprite sprite(data_->assets.getTexture("Pipe Down"));

		sprite.setPosition(data_->window.getSize().x, 0.f);

		pipeSprites_.push_back(sprite);
	}

	void Pipe::spawnInvisiblePipe()
	{
		sf::Sprite sprite(data_->assets.getTexture("Pipe Up"));

		sprite.setPosition(data_->window.getSize().x, data_->window.getSize().y - sprite.getGlobalBounds().height);
		sprite.setColor(sf::Color(0, 0, 0, 0));

		pipeSprites_.push_back(sprite);
	}

	void Pipe::movePipes(float dt)
	{
		for (unsigned short int i = 0; i < pipeSprites_.size(); i++)
		{
			sf::Vector2f position = pipeSprites_.at(i).getPosition();
			float movement = PIPE_MOVEMENT_SPEED * dt;

			pipeSprites_.at(i).move(-movement, 0);
		}
	}

	void Pipe::drawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites_.size(); i++)
		{
			data_->window.draw(pipeSprites_.at(i));
		}
	}
}