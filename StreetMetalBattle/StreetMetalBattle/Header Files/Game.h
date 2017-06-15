#pragma once
#include "ResourceHolder.h"
#include "StateStack.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include "Controller/Player.h"

class Game
{
public:
	Game();

	void registerStates();
	void processInput();
	void update(sf::Time dt);
	void run();
	void render();

private:
	sf::RenderWindow		mWindow;
	static const sf::Time	TimePerFrame;

	TextureHolder			mTextures;
	FontHolder				mFonts;
	Player					mPlayer;
	MusicPlayer				mMusic;
	SoundPlayer				mSounds;

	StateStack	mStateStack;

};