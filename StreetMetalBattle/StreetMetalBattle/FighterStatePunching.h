#pragma once
#include "FighterState.h"
#include "Animation.h"
#include "ResourceHolder.h"

class FighterStatePunching : public FighterState
{
	public:
		explicit FighterStatePunching(const TextureHolder& textures, int direction);
		~FighterStatePunching();
		FighterState* handleInput(Fighter& fighter, int input);
		FighterState*  update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
		void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
		sf::FloatRect getBoundingRect() const;
		sf::FloatRect getPunchBoundingRect() const;
		bool isHitting() const;

	private:
		Animation mFighterAnimation;
		int mOrientation;
		const TextureHolder& mTextures;
};