#pragma once
#include <SFML/Graphics.hpp>

struct FrameInfo
{
	sf::FloatRect boundingBox;
	sf::FloatRect boundingPunch;
};

struct AnimationInfo
{
	sf::Int16 textureId;
	sf::Vector2i frameSize;
	sf::Vector2i originalFrame;
	size_t numFrames;
	float numSecondsDuration;
	std::vector<FrameInfo> frames;
};

struct StateInfo
{
	AnimationInfo animation;
};

struct FighterInfo
{
	sf::Int16 hp;
	sf::Int16 speed;
	StateInfo die;
	StateInfo getPunched;
	StateInfo punching;
	StateInfo standBy;
	StateInfo walking;
};

std::vector<FighterInfo> initializeFighterData();