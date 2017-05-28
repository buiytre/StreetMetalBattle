#pragma once
#include "SFML\Graphics.hpp"
#include "Textures.h"
#include "Inputs.h"
#include "FighterData.h"
#include "Animation.h"

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