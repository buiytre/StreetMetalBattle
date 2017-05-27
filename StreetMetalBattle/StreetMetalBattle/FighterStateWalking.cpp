#include "FighterStateWalking.h"
#include "FighterStatePunching.h"
#include "FighterStateStandBy.h"
#include "Inputs.h"
#include "Fighter.h"
#include "Utility.h"

FighterStateWalking::FighterStateWalking(const TextureHolder & textures, int orientation)
	:	mTextures(textures)
{
	mFighterAnimation.setTexture(textures.get(texture));
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64 * 1));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(8);
	mFighterAnimation.setRepeating(true);
	mFighterAnimation.setDuration(sf::seconds(1));
	if (orientation == Orientation::LEFT)
	{
		mOrientation = Orientation::LEFT;
		mFighterAnimation.setScale(-2.f, 2.f);
	}
	else
	{
		orientation = Orientation::RIGHT;
		mFighterAnimation.setScale(2.f, 2.f);
	}
	centerOrigin(mFighterAnimation);
}

FighterStateWalking::~FighterStateWalking()
{
}

FighterState * FighterStateWalking::handleInput(Fighter & fighter, int input)
{
	switch (input)
	{
	case Inputs::Punch:
		return new FighterStatePunching(mTextures, mOrientation);
		break;
	case Inputs::MoveLeft:
		if (mOrientation != Orientation::LEFT)
		{
			mOrientation = Orientation::LEFT;
			mFighterAnimation.setScale(-2.f, 2.f);
		}		
		mVelocity.x -= speed;
		break;
	case Inputs::MoveRight:
		if (mOrientation != Orientation::RIGHT)
		{
			mOrientation = Orientation::RIGHT;
			mFighterAnimation.setScale(2.f, 2.f);
		}
		mVelocity.x += speed;
		break;
	case Inputs::MoveUp:
		mVelocity.y -= speed;
		break;
	case Inputs::MoveDown:
		mVelocity.y += speed;
		break;
	}
	return nullptr;
}

FighterState* FighterStateWalking::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	if (mVelocity.x == 0 && mVelocity.y == 0)
	{
		FighterState* state = new FighterStateStandBy(mTextures, mOrientation);
		return state->update(fighter, dt, commands);
	}

	fighter.setPosition(fighter.getPosition() + mVelocity * dt.asSeconds());
	mVelocity.x = 0;
	mVelocity.y = 0;
	mFighterAnimation.update(dt);
	return nullptr;
}

void FighterStateWalking::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::FloatRect FighterStateWalking::getBoundingRect() const
{
	return mFighterAnimation.getTransform().transformRect(sf::FloatRect(21.f, 25.f, 17.f, 29.f));
}
