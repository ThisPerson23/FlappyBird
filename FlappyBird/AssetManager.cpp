#include "AssetManager.h"

namespace FlappyBird
{
	void AssetManager::loadTexture(std::string name, std::string fileName)
	{
		sf::Texture texture;

		if (texture.loadFromFile(fileName))
		{
			this->textures_[name] = texture;
		}
	}

	sf::Texture& AssetManager::getTexture(std::string name)
	{
		return this->textures_.at(name);
	}

	void AssetManager::loadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->fonts_[name] = font;
		}
	}

	sf::Font& AssetManager::getFont(std::string name)
	{
		return this->fonts_.at(name);
	}

	void AssetManager::loadMusic(std::string name, std::string fileName)
	{
		this->music_[name] = fileName;
	}

	std::string AssetManager::getMusic(std::string name)
	{
		return this->music_.at(name);
	}

	void AssetManager::setIsMusicPaused(bool isPaused)
	{
		this->isMusicPaused_ = isPaused;
	}

	bool AssetManager::getIsMusicPaused() const
	{
		return this->isMusicPaused_;
	}
}