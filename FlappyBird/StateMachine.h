#pragma once

#include <memory>
#include <stack>

#include "State.h"

namespace FlappyBird
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() { }
		~StateMachine() { }

		void addState(StateRef newState, bool isReplacing = true);
		void removeState();

		void processStateChanges();

		StateRef& getActiveState();


	private:
		std::stack<StateRef> states_;
		StateRef			 newState_;

		bool				 isRemoving_;
		bool				 isAdding_;
		bool				 isReplacing_;
	};
}