#include "StateStack.h"
#include <cassert>


StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{
}

State::Ptr StateStack::createState(int stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for each (PendingChange change in mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateId));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}


void StateStack::update(sf::Time dt)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
		{
			return;
		}
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (State::Ptr& state : mStack)
	{
		state->draw();
	}

	applyPendingChanges();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
		{
			break;
		}
	}

	applyPendingChanges();
}

void StateStack::pushState(int stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

StateStack::PendingChange::PendingChange(Action action, int stateID) : action(action)
, stateId(stateID)
{
}
