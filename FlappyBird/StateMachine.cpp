#include "StateMachine.h"

namespace FlappyBird
{
	void StateMachine::addState(stateRef newState, bool isReplacing)
	{
		this->isAdding_ = true;
		this->isReplacing_ = isReplacing;
		this->newState_ = std::move(newState);
	}

	void StateMachine::removeState()
	{
		this->isRemoving_ = true;
	}

	void StateMachine::processStateChanges()
	{
		if (this->isRemoving_ && !this->states_.empty())
		{
			this->states_.pop();

			if (!this->states_.empty())
			{
				this->states_.top()->resume();
			}

			this->isRemoving_ = false;
		}

		if (this->isAdding_)
		{
			if (!this->states_.empty())
			{
				if (this->isReplacing_)
				{
					this->states_.pop();
				}
				else
				{
					this->states_.top()->pause();
				}
			}

			this->states_.push(std::move(this->newState_));
			this->states_.top()->init();
			this->isAdding_ = false;
		}
	}

	stateRef& StateMachine::getActiveState()
	{
		return this->states_.top();
	}
}