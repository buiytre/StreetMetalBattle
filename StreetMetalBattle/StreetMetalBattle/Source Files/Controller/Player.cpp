#include "Controller/Player.h"
#include "Entities/Fighter.h"
#include "Identifiers/Category.h"


Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Punch;

	mActionBinding[MoveLeft].action = derivedAction<Fighter>([](Fighter& f, sf::Time) 
	{
		f.moveLeft();
	});
	mActionBinding[MoveLeft].category = Category::PlayerFighter;

	mActionBinding[MoveRight].action = derivedAction<Fighter>([](Fighter& f, sf::Time)
	{
		f.moveRight();
	});
	mActionBinding[MoveRight].category = Category::PlayerFighter;

	mActionBinding[MoveUp].action = derivedAction<Fighter>([](Fighter& f, sf::Time)
	{
		f.moveUp();
	});
	mActionBinding[MoveUp].category = Category::PlayerFighter;


	mActionBinding[MoveDown].action = derivedAction<Fighter>([](Fighter& f, sf::Time)
	{
		f.moveDown();
	});
	mActionBinding[MoveDown].category = Category::PlayerFighter;

	mActionBinding[Punch].action = derivedAction<Fighter>([](Fighter& f, sf::Time)
	{
		f.punch();
	});
	mActionBinding[Punch].category = Category::PlayerFighter;

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
	case Player::Punch:
		return false;
	default:
		return false;
	}
}
