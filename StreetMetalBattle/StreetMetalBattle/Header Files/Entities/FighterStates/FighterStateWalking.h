#pragma once
#include "ResourceHolder.h"
#include "FighterState.h"

class FighterStateWalking : public FighterState
{
	public:
		explicit FighterStateWalking(const TextureHolder& textures, const FighterInfo& fighterInfo, int direction);
		~FighterStateWalking();
		FighterState* handleInput(Fighter& fighter, int input);
		void update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
	
	private:
		int mOrientation;
		sf::Vector2f mVelocity;
		const FighterInfo& mInfo;
		const TextureHolder& mTextures;
};