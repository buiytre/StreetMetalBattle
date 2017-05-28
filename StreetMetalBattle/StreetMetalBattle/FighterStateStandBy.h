#pragma once
#include "FighterState.h"
#include "Orientation.h"
#include "Animation.h"
#include "ResourceHolder.h"
#include "FighterData.h"

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
