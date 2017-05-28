#include "FighterStateWalking.h"
#include "FighterStatePunching.h"
#include "FighterStateStandBy.h"
#include "FighterStateGetPunched.h"
#include "FighterStateDying.h"
#include "Inputs.h"
#include "Fighter.h"
#include "Utility.h"
#include <iostream>

FighterStateWalking::FighterStateWalking(const TextureHolder & textures, const FighterInfo & fighterInfo, int direction)
	: mTextures(textures)
	, mInfo(fighterInfo)
{
	mAnimationInfo = mInfo.walking.animation;
	mFighterAnimation.setTexture(textures.get(mAnimationInfo.textureId));
	mFighterAnimation.setFrameSize(mAnimationInfo.frameSize);
	mFighterAnimation.setFrameOrigin(mAnimationInfo.originalFrame);
	mFighterAnimation.setNumFrames(mAnimationInfo.numFrames);
	mFighterAnimation.setRepeating(true);
	mFighterAnimation.setDuration(sf::seconds(mAnimationInfo.numSencondsDuration));
	if (direction == Orientation::LEFT)
	{
		mOrientation = Orientation::LEFT;
		mFighterAnimation.setScale(-1.f, 1.f);
	}
	else if (direction == Orientation::RIGHT)
	{
		mOrientation = Orientation::RIGHT;
		mFighterAnimation.setScale(1.f, 1.f);
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
			return new FighterStateStandBy(mTextures, mInfo, mOrientation);
		case Inputs::GetPunched:
			return new FighterStateGetPunched(mTextures, mInfo, mOrientation);
		case Inputs::Die:
			return new FighterStateDying(mTextures, mInfo, mOrientation);
		case Inputs::Punch:
			return new FighterStatePunching(mTextures, mInfo, mOrientation);
			break;
		case Inputs::MoveLeft:
			if (mOrientation != Orientation::LEFT)
			{
				mOrientation = Orientation::LEFT;
				mFighterAnimation.setScale(-1.f, 1.f);
			}		
			mVelocity.x -= mInfo.speed;
			break;
		case Inputs::MoveRight:
			if (mOrientation != Orientation::RIGHT)
			{
				mOrientation = Orientation::RIGHT;
				mFighterAnimation.setScale(1.f, 1.f);
			}
			mVelocity.x += mInfo.speed;
			break;
		case Inputs::MoveUp:
			mVelocity.y -= mInfo.speed;
			break;
		case Inputs::MoveDown:
			mVelocity.y += mInfo.speed;
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