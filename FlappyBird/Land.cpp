#include "Land.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{
	Land::Land(GameDataRef data)
		: data_(data)
	{
		sf::Sprite sprite(data_->assets.getTexture("Land"));
		sf::Sprite sprite2(data_->assets.getTexture("Land"));

		sprite.setPosition(0, data_->window.getSize().y - sprite.getGlobalBounds().height);
		sprite2.setPosition(sprite.getGlobalBounds().width, data_->window.getSize().y - sprite.getGlobalBounds().height);

		landSprites_.push_back(sprite);
		landSprites_.push_back(sprite2);
	}

	void Land::moveLand(float dt)
	{
		for (unsigned short int i = 0; i < landSprites_.size(); i++)
		{
			float movement = PIPE_MOVEMENT_SPEED * dt;

			landSprites_.at(i).move(-movement, 0.f);

			if (landSprites_.at(i).getPosition().x < 0 - landSprites_.at(i).getGlobalBounds().width)
			{
				sf::Vector2f position(data_->window.getSize().x, landSprites_.at(i).getPosition().y);

				landSprites_.at(i).setPosition(position);
			}
		}
	}

	void Land::drawLand()
	{
		for (unsigned short int i = 0; i < landSprites_.size(); i++)
		{
			data_->window.draw(landSprites_.at(i));
		}
	}
}