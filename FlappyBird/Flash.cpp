#include "Flash.h"

namespace FlappyBird
{
	Flash::Flash(GameDataRef data)
		: data_(data)
	{
		shape_ = sf::RectangleShape(sf::Vector2f(data_->window.getSize()));
		shape_.setFillColor(sf::Color(255, 255, 255, 0));

		flashOn_ = true;
	}

	void Flash::show(float dt)
	{
		if (flashOn_)
		{
			int alpha = (int)shape_.getFillColor().a + (FLASH_SPEED * dt);

			if (alpha >= 255.f)
			{
				alpha = 255.f;
				flashOn_ = false;
			}
			
			shape_.setFillColor(sf::Color(255, 255, 255, alpha));
		}
		else
		{
			int alpha = (int)shape_.getFillColor().a - (FLASH_SPEED * dt);

			if (alpha <= 0.f)
			{
				alpha = 0.f;
				flashOn_ = false;
			}

			shape_.setFillColor(sf::Color(255, 255, 255, alpha));
		}
	}

	void Flash::draw()
	{
		data_->window.draw(shape_);
	}
}