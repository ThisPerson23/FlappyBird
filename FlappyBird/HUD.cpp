#include "HUD.h"


namespace FlappyBird
{
	HUD::HUD(GameDataRef data)
		: data_(data)
	{
		scoreText_.setFont(data->assets.getFont("Flappy Font"));
		scoreText_.setString("0");
		scoreText_.setCharacterSize(128);
		scoreText_.setFillColor(sf::Color::White);
		scoreText_.setOrigin(scoreText_.getGlobalBounds().width / 2, scoreText_.getGlobalBounds().height / 2);
		scoreText_.setPosition(data_->window.getSize().x / 2, data_->window.getSize().y / 5);
	}

	void HUD::draw()
	{
		data_->window.draw(scoreText_);
	}

	void HUD::updateScore(int score)
	{
		scoreText_.setString(std::to_string(score));
	}
}