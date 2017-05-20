#include "Fighter.h"
#include "Utility.h"
#include "Textures.h"
#include "Category.h"
#include <iostream>

namespace {
	const int texture = Textures::TestFighter;
	const sf::IntRect textureRect(0, 0, 64, 64);
	const int speed = 100;
}

Fighter::Fighter(const TextureHolder & textures)
	: mFighterAnimation(textures.get(texture))
	, mOrientation(Right)
	, mVelocity(0.f,0.f)
	, mLastActionMoving(false)
{
	setStandByAnimation();
	centerOrigin(mFighterAnimation);
}

void Fighter::moveLeft()
{
	if (mOrientation == Right)
	{
		mFighterAnimation.setScale(-2.f, 2.f);
	}
	mVelocity.x -= speed;
	mOrientation = Left;
}

void Fighter::moveRight()
{
	if (mOrientation == Left)
	{
		mFighterAnimation.setScale(2.f, 2.f);
	}
	mVelocity.x += speed;
	mOrientation = Right;
}

void Fighter::moveUp()
{
	mVelocity.y -= speed;
}

void Fighter::moveDown()
{
	mVelocity.x += 0;
	mVelocity.y += speed;
}

void Fighter::updateCurrent(sf::Time dt, CommandQueue & commands)
{
	updateAnimation(dt);
	move(mVelocity * dt.asSeconds());
	mVelocity.x = 0;
	mVelocity.y = 0;
}

void Fighter::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

unsigned int Fighter::getCategory() const
{
	return Category::FIGHTER;
}

void Fighter::updateAnimation(sf::Time dt)
{
	if (!mLastActionMoving)
	{
		if (mVelocity.x != 0 || mVelocity.y != 0)
		{
			setWalkingAnimation();
			mLastActionMoving = true;
		}
	}
	else if (mLastActionMoving)
	{
		if (mVelocity.x == 0 && mVelocity.y == 0)
		{
			setStandByAnimation();
			mLastActionMoving = false;
		}
	}

	mFighterAnimation.update(dt);
}

void Fighter::setStandByAnimation()
{
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 0));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(4);
	mFighterAnimation.setRepeating(true);

	mFighterAnimation.setDuration(sf::seconds(1));
	if (mOrientation == Left)
	{
		mFighterAnimation.setScale(-2.f, 2.f);
	}
	else if (mOrientation == Right)
	{
		mFighterAnimation.setScale(2.f, 2.f);
	}

	mFighterAnimation.restart();
}

void Fighter::setWalkingAnimation()
{
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(8);
	mFighterAnimation.setRepeating(true);
	mFighterAnimation.setDuration(sf::seconds(1));

	if (mOrientation == Left)
	{
		mFighterAnimation.setScale(-2.f, 2.f);
	}
	else if (mOrientation == Right)
	{
		mFighterAnimation.setScale(2.f, 2.f);
	}

	mFighterAnimation.restart();
}