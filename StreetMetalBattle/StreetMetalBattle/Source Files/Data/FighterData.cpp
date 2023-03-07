#include "Data/FighterData.h"
#include "Identifiers/Textures.h"
#include "Entities/Fighter.h"
#include <sstream>
#include <fstream>

AnimationInfo loadAnimation(std::vector<std::string> animationInfo)
{
	size_t index = 0;
	AnimationInfo animation = AnimationInfo();
	animation.textureId = std::atoi(animationInfo[index++].c_str());
	int frameSizeX = std::atoi(animationInfo[index++].c_str());
	int frameSizeY = std::atoi(animationInfo[index++].c_str());
	animation.frameSize = sf::Vector2i(frameSizeX, frameSizeY);
	int originalFrameX = std::atoi(animationInfo[index++].c_str());
	int originalFrameY = std::atoi(animationInfo[index++].c_str());
	animation.originalFrame = sf::Vector2i(originalFrameX, originalFrameY);
	animation.numFrames = std::atoi(animationInfo[index++].c_str());
	animation.numSecondsDuration = std::stof(animationInfo[index++]);
	animation.frames = std::vector<FrameInfo>(animation.numFrames);
	
	for (size_t i = 0; i < animation.numFrames; i++)
	{
		animation.frames[i] = FrameInfo();
		size_t indexFrame = index + i * 10;
		animation.frames[i].boundingBox = sf::FloatRect(std::stof(animationInfo[indexFrame]), std::stof(animationInfo[indexFrame + 1]), std::stof(animationInfo[indexFrame + 2]), std::stof(animationInfo[indexFrame + 3]));
		animation.frames[i].boundingPunch = sf::FloatRect(std::stof(animationInfo[indexFrame + 4]), std::stof(animationInfo[indexFrame + 5]), std::stof(animationInfo[indexFrame + 6]), std::stof(animationInfo[indexFrame + 7]));
		animation.frames[i].offSetXYPosition = sf::Vector2f(std::stof(animationInfo[indexFrame + 8]), std::stof(animationInfo[indexFrame + 9]));
	}

	return animation;
}

FighterInfo loadFighterInfoFromParsedCsv(std::vector<std::vector<std::string>> parsedCsv)
{
	FighterInfo vFighterInfo = FighterInfo();
	vFighterInfo.hp = std::atoi(parsedCsv[0][0].c_str());
	vFighterInfo.speed = std::atoi(parsedCsv[0][1].c_str());

	vFighterInfo.die.animation = loadAnimation(parsedCsv[1]);
	vFighterInfo.getPunched.animation = loadAnimation(parsedCsv[2]);
	vFighterInfo.punching.animation = loadAnimation(parsedCsv[3]);
	vFighterInfo.standBy.animation = loadAnimation(parsedCsv[4]);
	vFighterInfo.walking.animation = loadAnimation(parsedCsv[5]);

	return vFighterInfo;
}

std::vector<FighterInfo> loadFighterInfoFromCSV(const std::string& filename)
{
	std::ifstream data;
	data.open(filename, std::ios::in);
	std::string line;
	std::vector<std::vector<std::string>> parsedCsv;
	if (data.is_open())
	{
		while (std::getline(data, line))
		{
			std::stringstream lineStream(line);
			std::string cell;
			std::vector<std::string> parsedRow;
			while (std::getline(lineStream, cell, ','))
			{
				parsedRow.push_back(cell);
			}
			parsedCsv.push_back(parsedRow);
		}
	}
	data.close();

	FighterInfo vFighterInfo = loadFighterInfoFromParsedCsv(parsedCsv);

	std::vector<FighterInfo> vFightersInfos;
	vFightersInfos.push_back(vFighterInfo);
	return vFightersInfos;
}





std::vector<FighterInfo> initializeFighterData()
{
	std::vector<FighterInfo> test = loadFighterInfoFromCSV("./Media/Sprites/test.fighter.csv");
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


	// Fighter::Player
	data[Fighter::Warrior].hp = 100;
	data[Fighter::Warrior].speed = 100;

	// Fighter::Player die animation
	data[Fighter::Warrior].die.animation.textureId = Textures::TestWarrior;
	data[Fighter::Warrior].die.animation.frameSize = sf::Vector2i(32, 64);
	data[Fighter::Warrior].die.animation.originalFrame = sf::Vector2i(0, 64 * 1);
	data[Fighter::Warrior].die.animation.numSecondsDuration = 1.f;
	data[Fighter::Warrior].die.animation.numFrames = 3;
	data[Fighter::Warrior].die.animation.frames = std::vector<FrameInfo>(data[Fighter::Warrior].die.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Warrior].die.animation.numFrames; i++)
	{
		data[Fighter::Warrior].die.animation.frames[i].boundingBox = sf::FloatRect();
		data[Fighter::Warrior].die.animation.frames[i].boundingPunch = sf::FloatRect();
		data[Fighter::Warrior].die.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 0.f);
	}

	// Fighter::Player get punched animation
	data[Fighter::Warrior].getPunched.animation.textureId = Textures::TestWarrior;
	data[Fighter::Warrior].getPunched.animation.frameSize = sf::Vector2i(32, 64);
	data[Fighter::Warrior].getPunched.animation.originalFrame = sf::Vector2i(32*3, 64 * 1);
	data[Fighter::Warrior].getPunched.animation.numSecondsDuration = 0.5f;
	data[Fighter::Warrior].getPunched.animation.numFrames = 2;
	data[Fighter::Warrior].getPunched.animation.frames = std::vector<FrameInfo>(data[Fighter::Warrior].getPunched.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Warrior].getPunched.animation.numFrames; i++)
	{
		data[Fighter::Warrior].getPunched.animation.frames[i].boundingBox = sf::FloatRect();
		data[Fighter::Warrior].getPunched.animation.frames[i].boundingPunch = sf::FloatRect();
		data[Fighter::Warrior].getPunched.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 0.f);
	}

	// Fighter::Player punching animation
	data[Fighter::Warrior].punching.animation.textureId = Textures::TestWarrior;
	data[Fighter::Warrior].punching.animation.frameSize = sf::Vector2i(32, 64);
	data[Fighter::Warrior].punching.animation.originalFrame = sf::Vector2i(32*7, 64 * 2);
	data[Fighter::Warrior].punching.animation.numSecondsDuration = 0.5f;
	data[Fighter::Warrior].punching.animation.numFrames = 2;
	data[Fighter::Warrior].punching.animation.frames = std::vector<FrameInfo>(data[Fighter::Warrior].punching.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Warrior].punching.animation.numFrames; i++)
	{
		data[Fighter::Warrior].punching.animation.frames[i].boundingBox = sf::FloatRect(7.f, 17.f, 20.f, 47.f);
		data[Fighter::Warrior].punching.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 0.f);
		if (i == 1)
		{
			data[Fighter::Warrior].punching.animation.frames[i].boundingPunch = sf::FloatRect(20.f, 35.f, 12.f, 3.f);
		}
		else
		{
			data[Fighter::Warrior].punching.animation.frames[i].boundingPunch = sf::FloatRect();
		}
	}

	// Fighter::Player standby animation
	data[Fighter::Warrior].standBy.animation.textureId = Textures::TestWarrior;
	data[Fighter::Warrior].standBy.animation.frameSize = sf::Vector2i(32, 64);
	data[Fighter::Warrior].standBy.animation.originalFrame = sf::Vector2i(0, 64 * 0);
	data[Fighter::Warrior].standBy.animation.numSecondsDuration = 1.f;
	data[Fighter::Warrior].standBy.animation.numFrames = 1;
	data[Fighter::Warrior].standBy.animation.frames = std::vector<FrameInfo>(data[Fighter::Warrior].standBy.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Warrior].standBy.animation.numFrames; i++)
	{
		data[Fighter::Warrior].standBy.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 0.f);
		data[Fighter::Warrior].standBy.animation.frames[i].boundingBox = sf::FloatRect(7.f, 17.f, 20.f, 47.f);
		data[Fighter::Warrior].standBy.animation.frames[i].boundingPunch = sf::FloatRect();
	}

	// Fighter::Player walking animation
	data[Fighter::Warrior].walking.animation.textureId = Textures::TestWarrior;
	data[Fighter::Warrior].walking.animation.frameSize = sf::Vector2i(32, 64);
	data[Fighter::Warrior].walking.animation.originalFrame = sf::Vector2i(32, 64 * 0);
	data[Fighter::Warrior].walking.animation.numSecondsDuration = 1.f;
	data[Fighter::Warrior].walking.animation.numFrames = 6;
	data[Fighter::Warrior].walking.animation.frames = std::vector<FrameInfo>(data[Fighter::Warrior].walking.animation.numFrames);
	for (size_t i = 0; i < data[Fighter::Warrior].walking.animation.numFrames; i++)
	{
		data[Fighter::Warrior].walking.animation.frames[i].offSetXYPosition = sf::Vector2f(0.f, 0.f);
		data[Fighter::Warrior].walking.animation.frames[i].boundingBox = sf::FloatRect(7.f, 17.f, 20.f, 47.f);
		data[Fighter::Warrior].walking.animation.frames[i].boundingPunch = sf::FloatRect();
	}
	

	return data;
}

