#pragma once
#include "FighterState.h"
#include "Animation.h"
#include "ResourceHolder.h"

class FighterStateGetPunched : public FighterState
{
public:
	explicit FighterStateGetPunched(const TextureHolder& textures, const FighterInfo& fighterInfo, int direction);
	~FighterStateGetPunched();
	FighterState* handleInput(Fighter& fighter, int input);
	void update(Fighter& fighter, sf::Time dt, CommandQueue & commands);

private:
	int mOrientation;
	const TextureHolder& mTextures;
	const FighterInfo& mInfo;
};