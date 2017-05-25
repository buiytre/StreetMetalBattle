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

Fighter::Fighter(Type type, const TextureHolder & textures, sf::Vector2f position, sf::Int16 hitPoints)
	: mFighterAnimation(textures.get(texture))
	, mOrientation(Right)
	, mVelocity(0.f, 0.f)
	, mPosition(position)
	, mType(type)
	, mPunching(false)
	, mPunchingCombo(false)
	, mLastAction(LastAction::None)
	, mBeingPunched(false)
	, mHitPoints(hitPoints)
	, mIsDying(false)
{
	setStandByAnimation();
	centerOrigin(mFighterAnimation);
}

void Fighter::moveLeft()
{
	if (mPunching)
	{
		return;
	}

	if (mOrientation == Right)
	{
		mFighterAnimation.setScale(-2.f, 2.f);
	}
	mVelocity.x -= speed;
	mOrientation = Left;
}

void Fighter::moveRight()
{
	if (mPunching)
	{
		return;
	}

	if (mOrientation == Left)
	{
		mFighterAnimation.setScale(2.f, 2.f);
	}
	mVelocity.x += speed;
	mOrientation = Right;
}

void Fighter::moveUp()
{
	if (mPunching)
	{
		return;
	}

	mVelocity.y -= speed;
}

void Fighter::moveDown()
{
	if (mPunching)
	{
		return;
	}

	mVelocity.y += speed;
}

void Fighter::punch()
{
	std::cout << "PUNCH! " << std::endl;
	if (mPunching && !mPunchingCombo) 
	{
		mPunchingCombo = true;
	}
	else 
	{
		mPunching = true;
		mTimeLastPunch = sf::Time::Zero;
	}
}

void Fighter::getHit(sf::Int16 damage)
{
	mHitPoints -= damage;
	mBeingPunched = true;
}

void Fighter::updateCurrent(sf::Time dt, CommandQueue & commands)
{
	updateAnimation(dt);
	move(mVelocity * dt.asSeconds());
	mPosition += mVelocity * dt.asSeconds();
	mVelocity.x = 0;
	mVelocity.y = 0;
	if (isDestroyed())
	{
		if (!mIsDying) 
		{
			setDyingAnimation();
			mIsDying = true;
		}
	}
	else if (mPunching) 
	{
		mTimeLastPunch += dt;
		if (mPunchingCombo) 
		{
			if (mTimeLastPunch > sf::seconds(1.f))
			{
				mPunching = false;
				mPunchingCombo = false;
			}
		} 
		else if (mTimeLastPunch > sf::seconds(0.5f)) 
		{
			mPunching = false;
		}
	}
}

void Fighter::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);

	drawBoundingPunch(target, states);
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

bool Fighter::isHitting()
{
	size_t currentFrame = mFighterAnimation.getCurrentFrame();
	return mPunching && (currentFrame == 4 || currentFrame == 5 || currentFrame == 7 || currentFrame == 8);
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
	if (mBeingPunched)
	{
		if (mLastAction != LastAction::BeingPunched)
		{
			setBeingPunchedAnimation();
			mLastAction = LastAction::BeingPunched;
		}
		else 
		{
			if (mFighterAnimation.isFinished())
			{
				mBeingPunched = false;
			}
		}
	}
	else if (mPunching && !mPunchingCombo)
	{
		if (mLastAction != LastAction::Punch)
		{
			setPunchingAnimation();
			mLastAction = LastAction::Punch;
		}
	}
	else if (mPunchingCombo) 
	{
		if (mLastAction != LastAction::Punch && mLastAction != LastAction::PunchCombo)
		{
			setPunchingAnimation();
			mFighterAnimation.setNumFrames(10);
			mFighterAnimation.setDuration(sf::seconds(1));
			mLastAction = LastAction::PunchCombo;
		}
		else if (mLastAction == LastAction::Punch)
		{
			mFighterAnimation.setNumFrames(10);
			mFighterAnimation.setDuration(sf::seconds(1));
			mLastAction = LastAction::PunchCombo;
		}
	}
	else if (mVelocity.x != 0 || mVelocity.y != 0)
	{
		if (mLastAction != LastAction::Moving)
		{
			setWalkingAnimation();
			mLastAction = LastAction::Moving;
		}
	}
	else if (mVelocity.x == 0 && mVelocity.y == 0)
	{
		if (mLastAction != LastAction::Stand) 
		{
			setStandByAnimation();
			mLastAction = LastAction::Stand;
		}
	}

	mFighterAnimation.update(dt);
}

void Fighter::setStandByAnimation()
{
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64*0));
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
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64*1));
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

void Fighter::setPunchingAnimation()
{
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64*9));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(6);
	mFighterAnimation.setRepeating(true);
	mFighterAnimation.setDuration(sf::seconds(0.5));

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

void Fighter::setBeingPunchedAnimation()
{
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64 * 4));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(2);
	mFighterAnimation.setRepeating(false);
	mFighterAnimation.setDuration(sf::seconds(0.5f));

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

void Fighter::setDyingAnimation()
{
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64 * 4));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(7);
	mFighterAnimation.setRepeating(false);
	mFighterAnimation.setDuration(sf::seconds(1.f));

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

bool Fighter::isDestroyed() const
{
	return mHitPoints <= 0;
}


bool Fighter::isMarkedForRemoval() const
{
	return (isDestroyed() && mFighterAnimation.isFinished());
}

sf::FloatRect Fighter::getBoundingRect() const
{
	return getWorldTransform().transformRect(mFighterAnimation.getTransform().transformRect(sf::FloatRect(21.f, 25.f, 17.f, 29.f)));
}

sf::FloatRect Fighter::getPunchBoundingRect() const
{
	switch (mLastAction)
	{
		case LastAction::Punch:
		case LastAction::PunchCombo:
		{
			size_t currentFrame = mFighterAnimation.getCurrentFrame();
			if (currentFrame == 4 || currentFrame == 5)
			{
				return getWorldTransform().transformRect(mFighterAnimation.getTransform().transformRect(sf::FloatRect(35.f, 40.f, 10.f, 6.f)));
			}
			if (currentFrame == 7 || currentFrame == 8)
			{
				return getWorldTransform().transformRect(mFighterAnimation.getTransform().transformRect(sf::FloatRect(32.f, 38.f, 10.f, 6.f)));
			}
		}
		default:
			return sf::FloatRect();
	}
}


void Fighter::drawBoundingPunch(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::FloatRect rect = getPunchBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}
