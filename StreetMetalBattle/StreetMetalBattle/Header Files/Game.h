#pragma once
#include "Header Files/ResourceHolder.h"
#include "Header Files/StateStack.h"
#include "Header Files/MusicPlayer.h"
#include "Header Files/SoundPlayer.h"
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