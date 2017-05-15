#include "Player.h"
#include <iostream>


Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
}

void Player::handleEvent(const sf::Event & event, CommandQueue & commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
		{
			commands.push(mActionBinding[found->second]);
		}
	}
}

void Player::handleRealtimeInput(CommandQueue & commands)
{
	for each (auto pair in mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
		{
			mKeyBinding.erase(itr++);
		}
		else
		{
			itr++;
		}
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for each (auto pair in mKeyBinding)
	{
		if (pair.second == action)
		{
			return pair.first;
		}
	}

	return sf::Keyboard::Unknown;
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case Player::MoveUp:
	case Player::MoveDown:
	case Player::MoveLeft:
	case Player::MoveRight:
		return true;
	default:
		return false;
	}
}
