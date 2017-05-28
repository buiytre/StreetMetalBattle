#pragma once
#include "FighterState.h"
#include "Animation.h"
#include "ResourceHolder.h"

class FighterStateDying : public FighterState
{
public:
	explicit FighterStateDying(const TextureHolder& textures, const FighterInfo& fighterInfo, int direction);
	~FighterStateDying();
	bool end() const;

private:
	int mOrientation;
	const TextureHolder& mTextures;
	const FighterInfo& mInfo;
};