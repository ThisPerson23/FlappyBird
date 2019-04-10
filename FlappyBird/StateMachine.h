#pragma once

#include <memory>
#include <stack>

#include "State.h"

namespace FlappyBird
{
	typedef std::unique_ptr<State> stateRef;

	class StateMachine
	{
	public:
		StateMachine() { }
		~StateMachine() { }

		void addState(stateRef newState, bool isReplacing = true);
		void removeState();

		void processStateChanges();

		stateRef& getActiveState();


	private:
		std::stack<stateRef> states_;
		stateRef			 newState_;

		bool				 isRemoving_;
		bool				 isAdding_;
		bool				 isReplacing_;
	};
}