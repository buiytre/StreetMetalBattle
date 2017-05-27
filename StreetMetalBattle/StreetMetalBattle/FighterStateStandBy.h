#pragma once
#include "FighterState.h"
#include "Orientation.h"
#include "Animation.h"
#include "ResourceHolder.h"

class FighterStateStandBy : public FighterState
{
	public:
		explicit FighterStateStandBy(const TextureHolder& textures, int direction);
		~FighterStateStandBy();
		FighterState* handleInput(Fighter& fighter, int input);
		FighterState* update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
		void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
		sf::FloatRect getBoundingRect() const;

	private:
		Animation mFighterAnimation;
		int mOrientation;
		const TextureHolder& mTextures;
};
