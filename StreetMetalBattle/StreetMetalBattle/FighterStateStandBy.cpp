#include "FighterStateStandBy.h"
#include "FighterStateWalking.h"
#include "FighterStatePunching.h"
#include "Inputs.h"
#include "Utility.h"
#include "FighterStateGetPunched.h"
#include "FighterStateDying.h"

FighterStateStandBy::FighterStateStandBy(const TextureHolder & textures, int orientation)
	: mTextures(textures)
	, mFighterAnimation(textures.get(texture))
{
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64 * 0));
	mFighterAnimation.setNumFrames(4);
	mFighterAnimation.setRepeating(true);

	mFighterAnimation.setDuration(sf::seconds(1));
	if (orientation == Orientation::LEFT)
	{
		mOrientation = Orientation::LEFT;
		mFighterAnimation.setScale(-2.f, 2.f);
	}
	else
	{
		mOrientation = Orientation::RIGHT;
		mFighterAnimation.setScale(2.f, 2.f);
	}
	centerOrigin(mFighterAnimation);
	mFighterAnimation.restart();
}

FighterStateStandBy::~FighterStateStandBy()
{
}

FighterState * FighterStateStandBy::handleInput(Fighter& fighter, int input)
{
	if (input == Inputs::MoveDown || input == Inputs::MoveUp || input == Inputs::MoveLeft || input == Inputs::MoveRight)
	{
		FighterState* state = new FighterStateWalking(mTextures, mOrientation);
		state->handleInput(fighter, input);
		return state;
	}
	if (input == Inputs::Punch)
	{
		return new FighterStatePunching(mTextures, mOrientation);
	}
	if (input == Inputs::GetPunched)
	{
		return new FighterStateGetPunched(mTextures, mOrientation);
	}
	if (input == Inputs::Die)
	{
		return new FighterStateDying(mTextures, mOrientation);
	}

	return nullptr;
}

void FighterStateStandBy::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	mFighterAnimation.update(dt);
}

void FighterStateStandBy::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::FloatRect FighterStateStandBy::getBoundingRect() const
{
	return mFighterAnimation.getTransform().transformRect(sf::FloatRect(21.f, 25.f, 17.f, 29.f));
}
