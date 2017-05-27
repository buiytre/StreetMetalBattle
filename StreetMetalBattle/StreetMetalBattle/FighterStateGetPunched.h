#pragma once
#include "FighterState.h"
#include "Animation.h"
#include "ResourceHolder.h"

class FighterStateGetPunched : public FighterState
{
public:
	explicit FighterStateGetPunched(const TextureHolder& textures, int direction);
	~FighterStateGetPunched();
	FighterState* handleInput(Fighter& fighter, int input);
	FighterState*  update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
	void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
	sf::FloatRect getBoundingRect() const;

private:
	Animation mFighterAnimation;
	int mOrientation;
	const TextureHolder& mTextures;
};