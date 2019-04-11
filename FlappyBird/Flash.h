#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

#include "DEFINITIONS.h"

namespace FlappyBird
{ 
	class Flash
	{
	public:
		Flash(GameDataRef data);

		void show(float dt);

		void draw();

	private:
		GameDataRef		   data_;

		sf::RectangleShape shape_;

		bool			   flashOn_;
	};
}