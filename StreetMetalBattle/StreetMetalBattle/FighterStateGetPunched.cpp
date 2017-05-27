#include "FighterStateGetPunched.h"
#include "FighterStateStandBy.h"
#include "FighterStateDying.h"
#include "Orientation.h"
#include "Utility.h"
#include "Command.h"
#include "Fighter.h"

FighterStateGetPunched::FighterStateGetPunched(const TextureHolder & textures, int direction)
	: mTextures(textures)
	, mFighterAnimation(textures.get(texture))
{
	mFighterAnimation.setFrameOrigin(sf::Vector2i(0, 64 * 4));
	mFighterAnimation.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mFighterAnimation.setNumFrames(2);
	mFighterAnimation.setRepeating(false);
	mFighterAnimation.setDuration(sf::seconds(0.5f));
	
	if (direction == Orientation::LEFT)
	{
		mOrientation = Orientation::LEFT;
		mFighterAnimation.setScale(-2.f, 2.f);
	}
	else if (direction == Orientation::RIGHT)
	{
		mOrientation = Orientation::RIGHT;
		mFighterAnimation.setScale(2.f, 2.f);
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
		return new FighterStateDying(mTextures, mOrientation);
	}
	if (input == Inputs::GoToStandBy)
	{
		return new FighterStateStandBy(mTextures, mOrientation);
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

void FighterStateGetPunched::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mFighterAnimation, states);
}

sf::FloatRect FighterStateGetPunched::getBoundingRect() const
{
	return sf::FloatRect();
}

