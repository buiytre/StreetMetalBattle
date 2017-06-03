#include "Entities/FighterStates/FighterState.h"

FighterState * FighterState::handleInput(Fighter & fighter, int input)
{
	return nullptr;
}

void FighterState::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	mFighterAnimation.update(dt);
}

void FighterState::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::FloatRect FighterState::getBoundingRect() const
{
	if (mFighterAnimation.isFinished())
	{
		return sf::FloatRect();
	}
	else 
	{
		return mFighterAnimation.getTransform().transformRect(mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].boundingBox);
	}
}

sf::FloatRect FighterState::getPunchBoundingRect() const
{
	if (mFighterAnimation.isFinished())
	{
		return sf::FloatRect();
	}
	else
	{
		return mFighterAnimation.getTransform().transformRect(mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].boundingPunch);
	}
}

bool FighterState::isHitting() const
{
	return false;
}

bool FighterState::end() const
{
	return false;
}
