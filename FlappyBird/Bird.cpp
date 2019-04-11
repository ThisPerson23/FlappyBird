#include "Bird.h"

namespace FlappyBird
{
	Bird::Bird(GameDataRef data)
		: data_(data)
	{
		birdSprite_.setTexture(data_->assets.getTexture("Bird Frame 1"));
	}

	void Bird::drawBird()
	{
		data_->window.draw(birdSprite_);
	}
}