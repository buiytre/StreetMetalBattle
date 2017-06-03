#pragma once
#include "Header Files/ResourceHolder.h"
#include "FighterState.h"

class FighterStatePunching : public FighterState
{
	public:
		explicit FighterStatePunching(const TextureHolder& textures, const FighterInfo& fighterInfo, int direction);
		~FighterStatePunching();
		FighterState* handleInput(Fighter& fighter, int input);
		void update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
		bool isHitting() const;

	private:
		int mOrientation;
		const TextureHolder& mTextures;
		const FighterInfo& mInfo;
};