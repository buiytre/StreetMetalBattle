#pragma once
#include "FighterState.h"
#include "Animation.h"
#include "ResourceHolder.h"

class FighterStateDying : public FighterState
{
public:
	explicit FighterStateDying(const TextureHolder& textures, int direction);
	~FighterStateDying();
	FighterState* handleInput(Fighter& fighter, int input);
	void update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
	void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
	sf::FloatRect getBoundingRect() const;
	bool end() const;

private:
	Animation mFighterAnimation;
	int mOrientation;
	const TextureHolder& mTextures;
};