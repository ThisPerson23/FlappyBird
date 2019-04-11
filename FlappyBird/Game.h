#pragma once

#include <memory>
#include <string>>

#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace FlappyBird
{ 
	struct GameData
	{
		StateMachine machine;
		AssetManager assets;
		InputManager input;
		sf::RenderWindow window;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		void run();

	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock clock_;

		GameDataRef data_ = std::make_shared<GameData>();
	};
}