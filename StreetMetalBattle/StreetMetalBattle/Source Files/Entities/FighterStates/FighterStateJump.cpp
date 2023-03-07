#include "Entities/FighterStates/FighterStateJump.h"
#include "Identifiers/Orientation.h"
#include "Utility.h"
#include "Entities/Fighter.h"
#include "Entities/FighterStates/FighterStateFalling.h"

FighterStateJump::FighterStateJump(const TextureHolder & textures, const FighterInfo & fighterInfo, int direction, sf::Vector2f initialAcceleration)
	: mTextures(textures)
	, mInfo(fighterInfo)
	, mAcceleration(initialAcceleration)
{
	mAnimationInfo = mInfo.walking.animation;
	mFighterAnimation.setTexture(textures.get(mAnimationInfo.textureId));
	mFighterAnimation.setFrameSize(mAnimationInfo.frameSize);
	mFighterAnimation.setFrameOrigin(mAnimationInfo.originalFrame);
	mFighterAnimation.setNumFrames(mAnimationInfo.numFrames);
	mFighterAnimation.setRepeating(true);
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
	centerBottom(mFighterAnimation);
	mFighterAnimation.restart();
	mStartToJump = true;
	mGravity = 90.8f;
	mActualHeight = 0.f;
}

FighterStateJump::~FighterStateJump()
{
}

FighterState * FighterStateJump::handleInput(Fighter & fighter, int input)
{
	if (input == Inputs::Falling)
	{
		return new FighterStateFalling(mTextures, mInfo, mOrientation, mAcceleration);
	}

	return nullptr;
}

void FighterStateJump::update(Fighter & fighter, sf::Time dt, CommandQueue & commands)
{
	mFighterAnimation.update(dt);
	mActualHeight = fighter.getHeight();
	mActualHeight = mActualHeight + mAcceleration.y * dt.asSeconds();
	fighter.setHeight(mActualHeight);
	fighter.setWantToWalkPosition(sf::Vector2f(fighter.getPosition().x + mAcceleration.x * dt.asSeconds(), 0));
	mAcceleration.y = mAcceleration.y - mGravity * dt.asSeconds();
	if (mActualHeight != 0.f)
	{
		mStartToJump = false;
	}
	if (mAcceleration.y <= 0.f)
	{
		Command goToFalling;
		goToFalling.category = fighter.getCategory();
		goToFalling.action = derivedAction<Fighter>([](Fighter& f, sf::Time)
		{
			f.Falling();
		});
		commands.push(goToFalling);
	}
}

void FighterStateJump::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::CircleShape shadow;
	shadow.setFillColor(sf::Color::Black);
	shadow.setRadius((mFighterAnimation.getFrameSize().x - mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].offSetXYPosition.x) / 2.f);
	sf::FloatRect bounds = shadow.getLocalBounds();
	shadow.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	shadow.setPosition(sf::Vector2f(-mFighterAnimation.getPosition().x / 2.f, mActualHeight));
	target.draw(shadow, states);

	states.transform.translate(mAnimationInfo.frames[mFighterAnimation.getCurrentFrame()].offSetXYPosition);
	target.draw(mFighterAnimation, states);
}
