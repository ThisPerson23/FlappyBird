#include "Pipe.h"

#include <iostream>

namespace FlappyBird
{
	Pipe::Pipe(GameDataRef data)
		: data_(data)
		, pipeSpawnYOffset_(0)
		, landHeight_(data_->assets.getTexture("Land").getSize().y)
	{}

	void Pipe::spawnBottomPipe()
	{
		sf::Sprite sprite(data_->assets.getTexture("Pipe Up"));

		sprite.setPosition(data_->window.getSize().x, data_->window.getSize().y - sprite.getGlobalBounds().height - pipeSpawnYOffset_);

		pipeSprites_.push_back(sprite);
	}

	void Pipe::spawnTopPipe()
	{
		sf::Sprite sprite(data_->assets.getTexture("Pipe Down"));

		sprite.setPosition(data_->window.getSize().x, -pipeSpawnYOffset_);

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
			if (pipeSprites_.at(i).getPosition().x < 0 - pipeSprites_.at(i).getGlobalBounds().width)
			{
				pipeSprites_.erase(pipeSprites_.begin() + i);
			}
			else
			{ 
				float movement = PIPE_MOVEMENT_SPEED * dt;

				pipeSprites_.at(i).move(-movement, 0.f);
			}
		}
	}

	void Pipe::drawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites_.size(); i++)
		{
			data_->window.draw(pipeSprites_.at(i));
		}
	}

	void Pipe::randomizePipeOffset()
	{
		pipeSpawnYOffset_ = rand() % (landHeight_ + 1);
	}

	const std::vector<sf::Sprite>& Pipe::getSprites() const
	{
		return pipeSprites_;
	}
}