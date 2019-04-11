#include "Bird.h"

namespace FlappyBird
{
	Bird::Bird(GameDataRef data)
		: data_(data)
		, animationIterator_(0)
		, birdState_(BIRD_STATE_STILL)
		, rotation_(0.f)
	{
		animationFrames_.push_back(data_->assets.getTexture("Bird Frame 1"));
		animationFrames_.push_back(data_->assets.getTexture("Bird Frame 2"));
		animationFrames_.push_back(data_->assets.getTexture("Bird Frame 3"));
		animationFrames_.push_back(data_->assets.getTexture("Bird Frame 4"));

		birdSprite_.setTexture(animationFrames_.at(animationIterator_));
		birdSprite_.setPosition((data_->window.getSize().x / 4.f) - (birdSprite_.getGlobalBounds().width / 2.f), (data_->window.getSize().y / 2.f) - (birdSprite_.getGlobalBounds().height / 2.f));

		sf::Vector2f origin = sf::Vector2f(birdSprite_.getGlobalBounds().width / 2.f, birdSprite_.getGlobalBounds().height / 2.f);

		birdSprite_.setOrigin(origin);
	}

	void Bird::drawBird()
	{
		data_->window.draw(birdSprite_);
	}
	void Bird::animateBird(float dt)
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
	void Bird::updateBird(float dt)
	{
		if (BIRD_STATE_FALLING == birdState_)
		{
			birdSprite_.move(0, GRAVITY * dt);

			rotation_ += ROTATION_SPEED * dt;

			if (rotation_ > 25.f)
			{
				rotation_ = 25.f;
			}

			birdSprite_.setRotation(rotation_);
		}
		else if (BIRD_STATE_FLYING == birdState_)
		{
			birdSprite_.move(0, -FLYING_SPEED * dt);

			rotation_ -= ROTATION_SPEED * dt;

			if (rotation_ < -25.f)
			{
				rotation_ = -25.f;
			}

			birdSprite_.setRotation(rotation_);
		}

		if (movementClock_.getElapsedTime().asSeconds() > FLYING_DURATION)
		{
			movementClock_.restart();

			birdState_ = BIRD_STATE_FALLING;
		}
	}

	void Bird::tap()
	{
		movementClock_.restart();

		birdState_ = BIRD_STATE_FLYING;
	}

	const sf::Sprite & Bird::getSprite() const
	{
		return birdSprite_;
	}
}