#include "FighterStateDying.h"
#include "Orientation.h"
#include "Utility.h"

FighterStateDying::FighterStateDying(const TextureHolder & textures, int direction)
	: mTextures(textures)
	, mFighterAnimation(textures.get(texture))
{
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64 * 4));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(7);
	mFighterAnimation.setRepeating(false);
	mFighterAnimation.setDuration(sf::seconds(1.f));
	
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
	mFighterAnimation.restart();
}

FighterStateDying::~FighterStateDying()
{
}

FighterState * FighterStateDying::handleInput(Fighter & fighter, int input)
{
	return nullptr;
}

void FighterStateDying::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	mFighterAnimation.update(dt);
}

void FighterStateDying::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::FloatRect FighterStateDying::getBoundingRect() const
{
	return sf::FloatRect();
}

bool FighterStateDying::end() const
{
	return mFighterAnimation.isFinished();
}
