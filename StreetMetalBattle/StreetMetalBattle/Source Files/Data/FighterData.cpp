#include "Data/FighterData.h"
#include "Identifiers/Textures.h"
#include "Entities/Fighter.h"

std::vector<FighterInfo> initializeFighterData()
{
	std::vector<FighterInfo> data(Fighter::TypeCount);

	// Fighter::Player
	data[Fighter::Player].hp = 100;
	data[Fighter::Player].speed = 100;

	// Fighter::Player die animation
	data[Fighter::Player].die.animation.textureId = Textures::TestFighter;
	data[Fighter::Player].die.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Player].die.animation.originalFrame = sf::Vector2i(0, 64 * 4);
	data[Fighter::Player].die.animation.numSecondsDuration = 1.f;
	data[Fighter::Player].die.animation.numFrames = 7;
	data[Fighter::Player].die.animation.frames = std::vector<FrameInfo>(data[Fighter::Player].die.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Player].die.animation.numFrames; i++)
	{
		data[Fighter::Player].die.animation.frames[i].boundingBox = sf::FloatRect();
		data[Fighter::Player].die.animation.frames[i].boundingPunch = sf::FloatRect();
		data[Fighter::Player].die.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
	}

	// Fighter::Player get punched animation
	data[Fighter::Player].getPunched.animation.textureId = Textures::TestFighter;
	data[Fighter::Player].getPunched.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Player].getPunched.animation.originalFrame = sf::Vector2i(0, 64 * 4);
	data[Fighter::Player].getPunched.animation.numSecondsDuration = 0.5f;
	data[Fighter::Player].getPunched.animation.numFrames = 2;
	data[Fighter::Player].getPunched.animation.frames = std::vector<FrameInfo>(data[Fighter::Player].getPunched.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Player].getPunched.animation.numFrames; i++)
	{
		data[Fighter::Player].getPunched.animation.frames[i].boundingBox = sf::FloatRect();
		data[Fighter::Player].getPunched.animation.frames[i].boundingPunch = sf::FloatRect();
		data[Fighter::Player].getPunched.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
	}

	// Fighter::Player punching animation
	data[Fighter::Player].punching.animation.textureId = Textures::TestFighter;
	data[Fighter::Player].punching.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Player].punching.animation.originalFrame = sf::Vector2i(0, 64 * 9);
	data[Fighter::Player].punching.animation.numSecondsDuration = 0.5f;
	data[Fighter::Player].punching.animation.numFrames = 6;
	data[Fighter::Player].punching.animation.frames = std::vector<FrameInfo>(data[Fighter::Player].punching.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Player].punching.animation.numFrames; i++)
	{
		data[Fighter::Player].punching.animation.frames[i].boundingBox = sf::FloatRect(21.f, 25.f, 17.f, 29.f);
		data[Fighter::Player].punching.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
		if (i == 4 || i == 5)
		{
			data[Fighter::Player].punching.animation.frames[i].boundingPunch = sf::FloatRect(35.f, 40.f, 10.f, 6.f);
		}
		else
		{
			data[Fighter::Player].punching.animation.frames[i].boundingPunch = sf::FloatRect();
		}
	}

	// Fighter::Player standby animation
	data[Fighter::Player].standBy.animation.textureId = Textures::TestFighter;
	data[Fighter::Player].standBy.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Player].standBy.animation.originalFrame = sf::Vector2i(0, 64 * 0);
	data[Fighter::Player].standBy.animation.numSecondsDuration = 1.f;
	data[Fighter::Player].standBy.animation.numFrames = 4;
	data[Fighter::Player].standBy.animation.frames = std::vector<FrameInfo>(data[Fighter::Player].standBy.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Player].standBy.animation.numFrames; i++)
	{
		data[Fighter::Player].standBy.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
		data[Fighter::Player].standBy.animation.frames[i].boundingBox = sf::FloatRect(21.f, 25.f, 17.f, 29.f);
		data[Fighter::Player].standBy.animation.frames[i].boundingPunch = sf::FloatRect();
	}

	// Fighter::Player walking animation
	data[Fighter::Player].walking.animation.textureId = Textures::TestFighter;
	data[Fighter::Player].walking.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Player].walking.animation.originalFrame = sf::Vector2i(0, 64 * 1);
	data[Fighter::Player].walking.animation.numSecondsDuration = 1.f;
	data[Fighter::Player].walking.animation.numFrames = 8;
	data[Fighter::Player].walking.animation.frames = std::vector<FrameInfo>(data[Fighter::Player].walking.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Player].walking.animation.numFrames; i++)
	{
		data[Fighter::Player].walking.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
		data[Fighter::Player].walking.animation.frames[i].boundingBox = sf::FloatRect(21.f, 25.f, 17.f, 29.f);
		data[Fighter::Player].walking.animation.frames[i].boundingPunch = sf::FloatRect();
	}

	// Figher::Enemy
	data[Fighter::Enemy].hp = 100;
	data[Fighter::Enemy].speed = 100;

	// Fighter::Enemy die animation
	data[Fighter::Enemy].die.animation.textureId = Textures::TestFighter;
	data[Fighter::Enemy].die.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Enemy].die.animation.originalFrame = sf::Vector2i(0, 64 * 4);
	data[Fighter::Enemy].die.animation.numSecondsDuration = 1.f;
	data[Fighter::Enemy].die.animation.numFrames = 7;
	data[Fighter::Enemy].die.animation.frames = std::vector<FrameInfo>(data[Fighter::Enemy].die.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Enemy].die.animation.numFrames; i++)
	{
		data[Fighter::Enemy].die.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
		data[Fighter::Enemy].die.animation.frames[i].boundingBox = sf::FloatRect();
		data[Fighter::Enemy].die.animation.frames[i].boundingPunch = sf::FloatRect();
	}

	//Fighter::Enemy get punched animation
	data[Fighter::Enemy].getPunched.animation.textureId = Textures::TestFighter;
	data[Fighter::Enemy].getPunched.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Enemy].getPunched.animation.originalFrame = sf::Vector2i(0, 64 * 4);
	data[Fighter::Enemy].getPunched.animation.numSecondsDuration = 0.5f;
	data[Fighter::Enemy].getPunched.animation.numFrames = 2;
	data[Fighter::Enemy].getPunched.animation.frames = std::vector<FrameInfo>(data[Fighter::Enemy].getPunched.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Enemy].getPunched.animation.numFrames; i++)
	{
		data[Fighter::Enemy].getPunched.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
		data[Fighter::Enemy].getPunched.animation.frames[i].boundingBox = sf::FloatRect();
		data[Fighter::Enemy].getPunched.animation.frames[i].boundingPunch = sf::FloatRect();
	}

	// Fighter::Player punching animation
	data[Fighter::Enemy].punching.animation.textureId = Textures::TestFighter;
	data[Fighter::Enemy].punching.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Enemy].punching.animation.originalFrame = sf::Vector2i(0, 64 * 9);
	data[Fighter::Enemy].punching.animation.numSecondsDuration = 0.5f;
	data[Fighter::Enemy].punching.animation.numFrames = 6;
	data[Fighter::Enemy].punching.animation.frames = std::vector<FrameInfo>(data[Fighter::Enemy].punching.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Enemy].punching.animation.numFrames; i++)
	{
		data[Fighter::Enemy].punching.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
		data[Fighter::Enemy].punching.animation.frames[i].boundingBox = sf::FloatRect(21.f, 25.f, 17.f, 29.f);

		if (i == 4 || i == 5)
		{
			data[Fighter::Enemy].punching.animation.frames[i].boundingPunch = sf::FloatRect(35.f, 40.f, 10.f, 6.f);
		}
		else
		{
			data[Fighter::Enemy].punching.animation.frames[i].boundingPunch = sf::FloatRect();
		}
	}

	// Fighter::Player standby animation
	data[Fighter::Enemy].standBy.animation.textureId = Textures::TestFighter;
	data[Fighter::Enemy].standBy.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Enemy].standBy.animation.originalFrame = sf::Vector2i(0, 64 * 0);
	data[Fighter::Enemy].standBy.animation.numSecondsDuration = 1.f;
	data[Fighter::Enemy].standBy.animation.numFrames = 4;
	data[Fighter::Enemy].standBy.animation.frames = std::vector<FrameInfo>(data[Fighter::Enemy].standBy.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Enemy].standBy.animation.numFrames; i++)
	{
		data[Fighter::Enemy].standBy.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
		data[Fighter::Enemy].standBy.animation.frames[i].boundingBox = sf::FloatRect(21.f, 25.f, 17.f, 29.f);
		data[Fighter::Enemy].standBy.animation.frames[i].boundingPunch = sf::FloatRect();
	}

	// Fighter::Player walking animation
	data[Fighter::Enemy].walking.animation.textureId = Textures::TestFighter;
	data[Fighter::Enemy].walking.animation.frameSize = sf::Vector2i(64, 64);
	data[Fighter::Enemy].walking.animation.originalFrame = sf::Vector2i(0, 64 * 1);
	data[Fighter::Enemy].walking.animation.numSecondsDuration = 1.f;
	data[Fighter::Enemy].walking.animation.numFrames = 8;
	data[Fighter::Enemy].walking.animation.frames = std::vector<FrameInfo>(data[Fighter::Enemy].walking.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Enemy].walking.animation.numFrames; i++)
	{
		data[Fighter::Enemy].walking.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 10.f);
		data[Fighter::Enemy].walking.animation.frames[i].boundingBox = sf::FloatRect(21.f, 25.f, 17.f, 29.f);
		data[Fighter::Enemy].walking.animation.frames[i].boundingPunch = sf::FloatRect();
	}

	return data;
}
