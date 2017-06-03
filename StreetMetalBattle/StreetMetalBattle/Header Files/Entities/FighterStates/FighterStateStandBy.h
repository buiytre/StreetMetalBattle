#pragma once
#include "Header Files/ResourceHolder.h"
#include "FighterState.h"

class FighterStateStandBy : public FighterState
{
	public:
		explicit FighterStateStandBy(const TextureHolder& textures, const FighterInfo& fighterInfo, int direction);
		~FighterStateStandBy();
		FighterState* handleInput(Fighter& fighter, int input);
		
	private:
		int mOrientation;
		const TextureHolder& mTextures;
		const FighterInfo& mInfo;
};
