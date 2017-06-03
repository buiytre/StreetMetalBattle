#include "Entities/FighterStates/FighterStateGetPunched.h"
#include "Entities/FighterStates/FighterStateStandBy.h"
#include "Entities/FighterStates/FighterStateDying.h"
#include "Identifiers/Orientation.h"
#include "Entities/Fighter.h"
#include "Header Files/Command.h"
#include "Header Files/Utility.h"

FighterStateGetPunched::FighterStateGetPunched(const TextureHolder & textures, const FighterInfo & fighterInfo, int direction)
	: mTextures(textures)
	, mInfo(fighterInfo)
{
	mAnimationInfo = mInfo.getPunched.animation;
	mFighterAnimation.setTexture(textures.get(mAnimationInfo.textureId));
	mFighterAnimation.setFrameSize(mAnimationInfo.frameSize);
	mFighterAnimation.setFrameOrigin(mAnimationInfo.originalFrame);
	mFighterAnimation.setNumFrames(mAnimationInfo.numFrames);
	mFighterAnimation.setRepeating(false);
	mFighterAnimation.setDuration(sf::seconds(mAnimationInfo.numSecondsDuration));
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

FighterStateGetPunched::~FighterStateGetPunched()
{
}

FighterState * FighterStateGetPunched::handleInput(Fighter & fighter, int input)
{
	if (input == Inputs::Die)
	{
		return new FighterStateDying(mTextures, mInfo, mOrientation);
	}
	if (input == Inputs::GoToStandBy)
	{
		return new FighterStateStandBy(mTextures, mInfo, mOrientation);
	}
	return nullptr;
}

void FighterStateGetPunched::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	mFighterAnimation.update(dt);
	if (mFighterAnimation.isFinished())
	{
		Command goToStandBy;
		goToStandBy.category = fighter.getCategory();
		goToStandBy.action = derivedAction<Fighter>([](Fighter& f, sf::Time)
		{
			f.goToStandBy();
		});
		commands.push(goToStandBy);
	}
}


