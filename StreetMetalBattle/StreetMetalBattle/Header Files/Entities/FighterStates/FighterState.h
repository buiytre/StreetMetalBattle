#pragma once
#include "Header Files/Animation.h"
#include "Identifiers/Textures.h"
#include "Identifiers/Inputs.h"
#include "Data/FighterData.h"

class Fighter;
class CommandQueue;

class FighterState
{
	public:
		virtual ~FighterState() {}
		virtual FighterState* handleInput(Fighter& fighter, int input);
		virtual void update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
		virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
		virtual sf::FloatRect getBoundingRect() const;
		virtual sf::FloatRect getPunchBoundingRect() const;
		virtual bool isHitting() const;
		virtual bool end() const;

	protected:
		AnimationInfo mAnimationInfo;
		Animation mFighterAnimation;
};