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
	if (!mFighterAnimation.isFinished())
	{
		states.transform.translate(mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].offSetXYPosition);
		target.draw(mFighterAnimation, states);
	}
}

sf::FloatRect FighterState::getBoundingRect() const
{
	if (mFighterAnimation.isFinished())
	{
		return sf::FloatRect();
	}
	else
	{
		sf::Vector2f offset = mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].offSetXYPosition;
		sf::FloatRect boundingBox = mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].boundingBox;
		boundingBox.left = boundingBox.left + offset.x;
		boundingBox.top = boundingBox.top + offset.y;
		return mFighterAnimation.getTransform().transformRect(boundingBox);
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
		sf::Vector2f offset = mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].offSetXYPosition;
		sf::FloatRect boundingBox = mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].boundingPunch;
		boundingBox.left = boundingBox.left + offset.x;
		boundingBox.top = boundingBox.top + offset.y;
		return mFighterAnimation.getTransform().transformRect(boundingBox);
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
