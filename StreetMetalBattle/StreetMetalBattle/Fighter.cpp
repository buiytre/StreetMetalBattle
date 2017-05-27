#include "Fighter.h"
#include "Utility.h"
#include "Textures.h"
#include "Category.h"
#include <iostream>
#include "FighterStateStandBy.h"
#include "FighterStateDying.h"
#include "FighterStateGetPunched.h"


Fighter::Fighter(Type type, const TextureHolder & textures, sf::Vector2f position, sf::Int16 hitPoints)
	: mPosition(position)
	, mType(type)
	, mHitPoints(hitPoints)
	, mTextures(textures)
	, mGetHitCommand()
{
	mState = new FighterStateStandBy(textures, Orientation::RIGHT);
	mGetHitCommand.category = getCategory();
	mGetHitCommand.action = [this, &textures](SceneNode& node, sf::Time)
	{
		if (mHitPoints <= 0)
		{
			handleInput(Inputs::Die);
		}
		else
		{
			handleInput(Inputs::GetPunched);
		}
	};
}

void Fighter::handleInput(int input)
{
	FighterState* state = mState->handleInput(*this, input);
	if (state != NULL)
	{
		delete mState;
		mState = state;
		mState->handleInput(*this, input);
	}
}

void Fighter::goToStandBy()
{
	handleInput(Inputs::GoToStandBy);
}

void Fighter::moveLeft()
{
	handleInput(Inputs::MoveLeft);
}

void Fighter::moveRight()
{
	handleInput(Inputs::MoveRight);
}

void Fighter::moveUp()
{
	handleInput(Inputs::MoveUp);
}

void Fighter::moveDown()
{
	handleInput(Inputs::MoveDown);
}

void Fighter::punch()
{
	handleInput(Inputs::Punch);
}

void Fighter::getHit(CommandQueue & commands, sf::Int16 damage)
{
	mHitPoints -= damage;
	commands.push(mGetHitCommand);
}

void Fighter::updateCurrent(sf::Time dt, CommandQueue & commands)
{
	mState->update(*this, dt, commands);
}

void Fighter::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	mState->drawCurrent(target, states);
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
	return mState->isHitting();
}

unsigned int Fighter::getCategory() const
{
	if (mType == Fighter::Type::Player) 
	{
		return Category::PlayerFighter;
	}

	return Category::EnemyFighter;
}

bool Fighter::isDestroyed() const
{
	return mHitPoints <= 0;
}

bool Fighter::isMarkedForRemoval() const
{
	return (isDestroyed() && mState->end());
}

sf::FloatRect Fighter::getBoundingRect() const
{
	return getWorldTransform().transformRect(mState->getBoundingRect());
}

sf::FloatRect Fighter::getPunchBoundingRect() const
{
	return getWorldTransform().transformRect(mState->getPunchBoundingRect());
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
