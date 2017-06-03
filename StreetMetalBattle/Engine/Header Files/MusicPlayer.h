#pragma once
#include <SFML\Audio.hpp>
#include "ResourceHolder.h"

class MusicPlayer : private sf::NonCopyable
{
public:
	MusicPlayer();

	void play(int theme);
	void stop();

	void setPaused(bool paused);
	void setVolume(float volume);

private:
	sf::Music mMusic;
	std::map<int, std::string> mFilenames;
	float mVolume;
};