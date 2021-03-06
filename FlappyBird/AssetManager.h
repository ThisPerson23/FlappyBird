#pragma once

#include <map>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "DEFINITIONS.h"

namespace FlappyBird
{ 
	class AssetManager
	{
	public:
		AssetManager() : isMusicPaused_(false) { this->music_["Game Tune"] = GAME_MUSIC_FILEPATH; };
		~AssetManager() { };

		void loadTexture(std::string name, std::string fileName);
		sf::Texture& getTexture(std::string name);

		void loadFont(std::string name, std::string fileName);
		sf::Font& getFont(std::string name);

		void loadMusic(std::string name, std::string fileName);
		std::string getMusic(std::string name);

		void setIsMusicPaused(bool isPaused);
		bool getIsMusicPaused() const;

	private:
		std::map<std::string, sf::Texture>		textures_;
		std::map<std::string, sf::Font>			fonts_;
		std::map<std::string, std::string>		music_;

		bool									isMusicPaused_;
	};
}