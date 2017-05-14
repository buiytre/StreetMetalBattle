#include "TitleState.h"
#include <utility>
#include "ResourceHolder.h"
#include "SFML\Graphics.hpp"
#include "Utility.h"
#include "Fonts.h"

TitleState::TitleState(StateStack & stack, Context context)
	: State(stack, context)
	, mTitle()
	, mPressAnyKey()
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	mTitle.setFont(context.fonts->get(Fonts::TITLE));
	mTitle.setString("STREET METAL BATTLE");
	centerOrigin(mTitle);
	mPressAnyKey.setScale(2.f, 2.f);
	mTitle.setPosition(context.window->getView().getSize().x / 2.f, context.window->getView().getSize().x / 4.f);

	mPressAnyKey.setFont(context.fonts->get(Fonts::TITLE));
	mPressAnyKey.setString("Press any key to continue");
	centerOrigin(mPressAnyKey);
	mPressAnyKey.setScale(0.5f, 0.5f);
	mPressAnyKey.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mTitle);

	if (mShowText)
	{
		window.draw(mPressAnyKey);
	}
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		//requestStackPush(States::Menu);
	}

	return true;
}
