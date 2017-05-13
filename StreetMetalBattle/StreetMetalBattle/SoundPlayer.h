#pragma once
#include <SFML\Audio.hpp>
#include <list>
#include "ResourceHolder.h"

class SoundPlayer : private sf::NonCopyable
{
public:
	SoundPlayer();

	void play(int effect);
	void play(int effect, sf::Vector2f position);

	void removeStoppedSounds();
	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;

private:
	SoundBufferHolder mSoundBuffers;
	std::list<sf::Sound> mSounds;
};