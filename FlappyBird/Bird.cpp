#include "Bird.h"

namespace FlappyBird
{
	Bird::Bird(GameDataRef data)
		: data_(data)
		, animationIterator_(0)
	{
		animationFrames_.push_back(data_->assets.getTexture("Bird Frame 1"));
		animationFrames_.push_back(data_->assets.getTexture("Bird Frame 2"));
		animationFrames_.push_back(data_->assets.getTexture("Bird Frame 3"));
		animationFrames_.push_back(data_->assets.getTexture("Bird Frame 4"));

		birdSprite_.setTexture(animationFrames_.at(animationIterator_));
	}

	void Bird::drawBird()
	{
		data_->window.draw(birdSprite_);
	}
	void Bird::animate(float dt)
	{
		if (clock_.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / animationFrames_.size())
		{
			if (animationIterator_ < animationFrames_.size() - 1)
			{
				animationIterator_++;
			}
			else
			{
				animationIterator_ = 0;
			}

			birdSprite_.setTexture(animationFrames_.at(animationIterator_));

			clock_.restart();
		}
	}
}