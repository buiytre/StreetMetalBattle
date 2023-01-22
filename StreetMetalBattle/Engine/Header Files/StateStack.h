#pragma once
#include <functional>
#include <map>
#include <vector>
#include <utility>
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "State.h"

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit StateStack(State::Context context);

	template <typename T>
	void registerState(int stateID);

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);

	void pushState(int stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
	State::Ptr createState(int stateID);
	void applyPendingChanges();

private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, int stateID = 0);

		Action action;
		int stateId;
	};

private:
	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;
	std::map<int, std::function<State::Ptr()>> mFactories;
};


