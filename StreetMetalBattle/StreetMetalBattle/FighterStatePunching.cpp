#include "FighterStatePunching.h"
#include "FighterStateStandBy.h"
#include "Orientation.h"
#include "Utility.h"

FighterStatePunching::FighterStatePunching(const TextureHolder & textures, int direction)
	: mTextures(textures)
{
	mFighterAnimation.setTexture(textures.get(texture));
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64 * 9));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(6);
	mFighterAnimation.setRepeating(false);
	mFighterAnimation.setDuration(sf::seconds(0.5));

	if (direction == Orientation::LEFT)
	{
		mOrientation = Orientation::LEFT;
		mFighterAnimation.setScale(-2.f, 2.f);
	}
	else if (direction == Orientation::RIGHT)
	{
		mOrientation = Orientation::RIGHT;
		mFighterAnimation.setScale(2.f, 2.f);
	}
	centerOrigin(mFighterAnimation);
}

FighterStatePunching::~FighterStatePunching()
{
}

FighterState * FighterStatePunching::handleInput(Fighter & fighter, int input)
{
	return nullptr;
}

FighterState* FighterStatePunching::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	mFighterAnimation.update(dt);
	if (mFighterAnimation.isFinished())
	{
		FighterState* state = new FighterStateStandBy(mTextures, mOrientation);
		state->update(fighter, dt, commands);
		return state;
	}
	return nullptr;
}

void FighterStatePunching::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::FloatRect FighterStatePunching::getBoundingRect() const
{
	return mFighterAnimation.getTransform().transformRect(sf::FloatRect(21.f, 25.f, 17.f, 29.f));
}

sf::FloatRect FighterStatePunching::getPunchBoundingRect() const
{
	size_t currentFrame = mFighterAnimation.getCurrentFrame();
	if (currentFrame == 4 || currentFrame == 5)
	{
		return mFighterAnimation.getTransform().transformRect(sf::FloatRect(35.f, 40.f, 10.f, 6.f));
	}
	if (currentFrame == 7 || currentFrame == 8)
	{
		return mFighterAnimation.getTransform().transformRect(sf::FloatRect(32.f, 38.f, 10.f, 6.f));
	}
	return sf::FloatRect();
}

bool FighterStatePunching::isHitting() const
{
	return true;
}
