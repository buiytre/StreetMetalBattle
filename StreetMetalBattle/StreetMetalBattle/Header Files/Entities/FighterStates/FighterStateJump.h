#pragma once
#include "ResourceHolder.h"
#include "FighterState.h"

class FighterStateJump : public FighterState
{
public:
	explicit FighterStateJump(const TextureHolder& textures, const FighterInfo& fighterInfo, int direction, sf::Vector2f initialAcceleration/*, float gravity*/);
	~FighterStateJump();
	FighterState* handleInput(Fighter& fighter, int input);
	void update(Fighter& fighter, sf::Time dt, CommandQueue & commands);
	void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	int mOrientation;
	const TextureHolder& mTextures;
	const FighterInfo& mInfo;
	sf::Vector2f mAcceleration;
	float mGravity;
	bool mStartToJump;
	float mActualHeight;
};