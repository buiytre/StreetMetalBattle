#include "Entities/Fighter.h"
#include "Header Files/Utility.h"
#include "Identifiers/Textures.h"
#include "Identifiers/Category.h"
#include "Identifiers/Orientation.h"
#include "Entities/FighterStates/FighterStateStandBy.h"
#include "Entities/FighterStates/FighterStateDying.h"
#include "Entities/FighterStates/FighterStateGetPunched.h"
#include "Data/FighterData.h"

namespace
{
	const std::vector<FighterInfo> Table = initializeFighterData();
}

Fighter::Fighter(Type type, const TextureHolder & textures, sf::Int32 fighterId, sf::Vector2f position, sf::Int16 hitPoints)
	: mPosition(position)
	, mType(type)
	, mHitPoints(hitPoints)
	, mTextures(textures)
	, mGetHitCommand()
	, mFighterId(fighterId)
	, mWantToWalk(position)
{
	mState = new FighterStateStandBy(textures, Table[type], Orientation::RIGHT);
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
	drawBoundingPunch(target, states);
}

sf::Vector2f Fighter::getWorldPosition() const
{
	return mPosition;
}

sf::Vector2f Fighter::getWantToWalkPosition() const
{
	return mWantToWalk;
}

void Fighter::setPosition(const sf::Vector2f & position)
{
	mPosition = position;
	SceneNode::setPosition(position);
}

void Fighter::setWantToWalkPosition(const sf::Vector2f & position)
{
	mWantToWalk = position;
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

sf::Int32 Fighter::getIdentifier()
{
	return mFighterId;
}

void Fighter::setIdentifier(sf::Int32 identifier)
{
	mFighterId = identifier;
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

	sf::RectangleShape background;
	background.setPosition(sf::Vector2f(rect.left, rect.top));
	background.setSize(sf::Vector2f(rect.width, rect.height));
	background.setFillColor(sf::Color(255,0,0,50));
	background.setOutlineColor(sf::Color::Red);

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.f);
	target.draw(background);
	target.draw(shape);
}
