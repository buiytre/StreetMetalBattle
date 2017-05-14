#pragma once
#include "State.h"
#include "SFML\Graphics.hpp"

class TitleState : State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Text mTitle;
	sf::Text mPressAnyKey;

	bool mShowText;
	sf::Time mTextEffectTime;
};