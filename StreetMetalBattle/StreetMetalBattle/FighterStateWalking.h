#pragma once
#include "FighterState.h"
#include "Orientation.h"
#include "Animation.h"
#include "ResourceHolder.h"

class FighterStateWalking : public FighterState
{
	public:
		explicit FighterStateWalking(const TextureHolder& textures, int direction);
		~FighterStateWalking();
		FighterState* handleInput(Fighter& fighter, int input);
		void update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
		void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
		sf::FloatRect getBoundingRect() const;
	
	private:
		Animation mFighterAnimation;
		int mOrientation;
		sf::Vector2f mVelocity;
		const TextureHolder& mTextures;
};