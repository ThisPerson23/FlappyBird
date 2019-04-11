#include "Pipe.h"

namespace FlappyBird
{
	Pipe::Pipe(GameDataRef data)
		: data_(data)
	{}

	void Pipe::drawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites_.size(); i++)
		{
			data_->window.draw(pipeSprites_.at(i));
		}
	}
}