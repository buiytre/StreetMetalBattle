#include "FighterStateWalking.h"
#include "FighterStatePunching.h"
#include "FighterStateStandBy.h"
#include "FighterStateGetPunched.h"
#include "FighterStateDying.h"
#include "Inputs.h"
#include "Fighter.h"
#include "Utility.h"
#include <iostream>

FighterStateWalking::FighterStateWalking(const TextureHolder & textures, int orientation)
	:	mTextures(textures)
	,	mFighterAnimation(textures.get(texture))
{	
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
		mOrientation = Orientation::RIGHT;
		mFighterAnimation.setScale(2.f, 2.f);
	}
	centerOrigin(mFighterAnimation);
	mFighterAnimation.restart();
}

FighterStateWalking::~FighterStateWalking()
{
}

FighterState * FighterStateWalking::handleInput(Fighter & fighter, int input)
{
	switch (input)
	{
	case Inputs::GoToStandBy:
			return new FighterStateStandBy(mTextures, mOrientation);
		case Inputs::GetPunched:
			return new FighterStateGetPunched(mTextures, mOrientation);
		case Inputs::Die:
			return new FighterStateDying(mTextures, mOrientation);
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

void FighterStateWalking::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	mFighterAnimation.update(dt);
	if (mVelocity.x == 0 && mVelocity.y == 0)
	{
		Command goToStandBy;
		goToStandBy.category = fighter.getCategory();
		goToStandBy.action = derivedAction<Fighter>([](Fighter& f, sf::Time)
		{
			f.goToStandBy();
		});
		commands.push(goToStandBy);
	}

	fighter.setPosition(fighter.getPosition() + mVelocity * dt.asSeconds());
	mVelocity.x = 0;
	mVelocity.y = 0;
}

void FighterStateWalking::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::FloatRect FighterStateWalking::getBoundingRect() const
{
	return mFighterAnimation.getTransform().transformRect(sf::FloatRect(21.f, 25.f, 17.f, 29.f));
}
