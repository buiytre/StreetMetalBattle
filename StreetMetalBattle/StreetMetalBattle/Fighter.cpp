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

Fighter::Fighter(Type type, const TextureHolder & textures, sf::Vector2f position)
	: mFighterAnimation(textures.get(texture))
	, mOrientation(Right)
	, mVelocity(0.f, 0.f)
	, mLastActionMoving(false)
	, mPosition(position)
	, mType(type)
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
	mPosition += mVelocity * dt.asSeconds();
	mVelocity.x = 0;
	mVelocity.y = 0;
	std::cout << "X: " << mPosition.x << "Y: " << mPosition.y << std::endl;
}

void Fighter::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::Vector2f Fighter::getWorldPosition() const
{
	return mPosition;
}

void Fighter::setPosition(const sf::Vector2f & position)
{
	mPosition = position;
	SceneNode::setPosition(position);
}

unsigned int Fighter::getCategory() const
{
	if (mType == Fighter::Type::Player) 
	{
		return Category::PlayerFighter;
	}

	return Category::EnemyFighter;
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
