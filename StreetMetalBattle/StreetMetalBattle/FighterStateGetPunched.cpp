#include "FighterStateGetPunched.h"
#include "FighterStateStandBy.h"
#include "FighterStateDying.h"
#include "Orientation.h"
#include "Utility.h"

FighterStateGetPunched::FighterStateGetPunched(const TextureHolder & textures, int direction)
	: mTextures(textures)
{
	mFighterAnimation.setTexture(textures.get(texture));
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64 * 4));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(2);
	mFighterAnimation.setRepeating(false);
	mFighterAnimation.setDuration(sf::seconds(0.5f));
	
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

FighterStateGetPunched::~FighterStateGetPunched()
{
}

FighterState * FighterStateGetPunched::handleInput(Fighter & fighter, int input)
{
	if (input == Inputs::Die)
	{
		return new FighterStateDying(mTextures, mOrientation);
	}
	return nullptr;
}

FighterState * FighterStateGetPunched::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	if (!mFighterAnimation.isFinished()) 
	{
		mFighterAnimation.update(dt);
		return nullptr;
	}

	FighterState* state = new FighterStateStandBy(mTextures, mOrientation);
	state->update(fighter, dt, commands);
	return state;
}

void FighterStateGetPunched::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::FloatRect FighterStateGetPunched::getBoundingRect() const
{
	return sf::FloatRect();
}

