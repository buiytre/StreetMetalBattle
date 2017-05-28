#include "FighterStateStandBy.h"
#include "FighterStateWalking.h"
#include "FighterStatePunching.h"
#include "Inputs.h"
#include "Utility.h"
#include "FighterStateGetPunched.h"
#include "FighterStateDying.h"

FighterStateStandBy::FighterStateStandBy(const TextureHolder & textures, const FighterInfo& fighterInfo, int orientation)
	: mTextures(textures)
	, mInfo(fighterInfo)
{
	mAnimationInfo = mInfo.standBy.animation;
	mFighterAnimation.setTexture(textures.get(mAnimationInfo.textureId));
	mFighterAnimation.setFrameSize(mAnimationInfo.frameSize);
	mFighterAnimation.setFrameOrigin(mAnimationInfo.originalFrame);
	mFighterAnimation.setNumFrames(mAnimationInfo.numFrames);
	mFighterAnimation.setRepeating(true);
	mFighterAnimation.setDuration(sf::seconds(mAnimationInfo.numSencondsDuration));
	if (orientation == Orientation::LEFT)
	{
		mOrientation = Orientation::LEFT;
		mFighterAnimation.setScale(-1.f, 1.f);
	}
	else if (orientation == Orientation::RIGHT)
	{
		mOrientation = Orientation::RIGHT;
		mFighterAnimation.setScale(1.f, 1.f);
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
		FighterState* state = new FighterStateWalking(mTextures, mInfo, mOrientation);
		state->handleInput(fighter, input);
		return state;
	}
	if (input == Inputs::Punch)
	{
		return new FighterStatePunching(mTextures, mInfo, mOrientation);
	}
	if (input == Inputs::GetPunched)
	{
		return new FighterStateGetPunched(mTextures, mInfo, mOrientation);
	}
	if (input == Inputs::Die)
	{
		return new FighterStateDying(mTextures, mInfo, mOrientation);
	}

	return nullptr;
}