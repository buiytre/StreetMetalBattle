#include "FighterStateDying.h"
#include "Orientation.h"
#include "Utility.h"

FighterStateDying::FighterStateDying(const TextureHolder & textures, const FighterInfo & fighterInfo, int direction)
	: mTextures(textures)
	, mInfo(fighterInfo)
{
	mAnimationInfo = mInfo.die.animation;
	mFighterAnimation.setTexture(textures.get(mAnimationInfo.textureId));
	mFighterAnimation.setFrameSize(mAnimationInfo.frameSize);
	mFighterAnimation.setFrameOrigin(mAnimationInfo.originalFrame);
	mFighterAnimation.setNumFrames(mAnimationInfo.numFrames);
	mFighterAnimation.setRepeating(false);
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

FighterStateDying::~FighterStateDying()
{
}

bool FighterStateDying::end() const
{
	return mFighterAnimation.isFinished();
}