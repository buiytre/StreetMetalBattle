#include "World/WorldMap.h"
#include "Identifiers/Textures.h"
#include "SpriteNode.h"
#include "Identifiers/Category.h"
#include <algorithm>
#include "Utility.h"
#include "World/Scenario/TileMapLoader.h"

WorldMap::WorldMap(sf::RenderWindow & window, FontHolder& fonts)
	: mTarget(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mFonts(fonts)
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(
		0.f, //left x position
		0.f, //top y position
		mWorldView.getSize().x, //width
		mWorldView.getSize().y) //height
	, mCommandQueue()
	, mCameraPosition(
		512, // x
		384) //y
	, mTileMap()
{
	loadTextures();
	buildLevelMap();
	buildScene();
}

void WorldMap::update(sf::Time dt)
{
	while (!mCommandQueue.isEmpty())
	{
		Command command = mCommandQueue.pop();
		mSceneGraph.onCommand(command, dt);
	}

	mSceneGraph.update(dt, mCommandQueue);

	handleCollisions();
	CheckDeathFighters();
	//mWorldView.setCenter(mPlayer->getWorldPosition());
	mWorldView.setCenter(mCameraPosition);
	CheckFightersInsideZone();
}

void WorldMap::CheckFightersInsideZone()
{
	for (Fighter* f : mFighters)
	{
		sf::Vector2f actualPosition = f->getPosition();
		sf::Vector2f wantToWalkTo = f->getWantToWalkPosition();
		if (actualPosition.x == wantToWalkTo.x && actualPosition.y == wantToWalkTo.y)
		{
			continue;
		}

		if (mTileMap.canWalk(wantToWalkTo))
		{
			(*f).setPosition(wantToWalkTo);
			continue;
		}

		if (actualPosition.y - wantToWalkTo.y < 0)
		{
			sf::Vector3f fallingPosition = mTileMap.canFall(actualPosition, wantToWalkTo);
			if (!(fallingPosition.x == 0.f && fallingPosition.y == 0.f && fallingPosition.z == 0.f))
			{
				(*f).Falling();
				(*f).setHeight(fallingPosition.z);
				(*f).setPosition(sf::Vector2f(fallingPosition.x, fallingPosition.y));
				continue;
			}
		}

		sf::Vector2f positionX = sf::Vector2f(wantToWalkTo.x, actualPosition.y);
		if (mTileMap.canWalk(positionX))
		{
			(*f).setPosition(positionX);
			continue;
		}

		sf::Vector2f positionY = sf::Vector2f(actualPosition.x, wantToWalkTo.y);
		if (mTileMap.canWalk(positionY)) 
		{
			(*f).setPosition(positionY);
			continue;
		}	
	}
}

void WorldMap::handleCollisions()
{
	for (size_t i = 0; i < mFighters.size(); i++)
	{
		for (size_t j = 0; j < mFighters.size(); j++)
		{
			if (i != j)
			{
				bool touch = (*mFighters[i]).getBoundingRect().intersects((*mFighters[j]).getBoundingRect());
				bool hit = (*mFighters[i]).getPunchBoundingRect().intersects((*mFighters[j]).getBoundingRect());
				if (touch && !hit) 
				{
					sf::Vector2f fighterOne = (*mFighters[i]).getPosition();
					sf::Vector2f fighterTwo = (*mFighters[j]).getPosition();
					float diff = std::abs(fighterOne.y - fighterTwo.y);
					if (diff <= 20.f)
					{
						(*mFighters[j]).setWantToWalkPosition(unitVector(fighterTwo - fighterOne) + fighterTwo);
					}
				}
				else if (hit) 
				{
					sf::Vector2f fighterOne = (*mFighters[i]).getPosition();
					sf::Vector2f fighterTwo = (*mFighters[j]).getPosition();
					float diff = std::abs(fighterOne.y - fighterTwo.y);
					if (diff <= 20.f)
					{
						(*mFighters[j]).getHit(mCommandQueue, 10);
						(*mFighters[j]).setWantToWalkPosition(unitVector(fighterTwo - fighterOne)*2.f + fighterTwo);
					}
				}
			}
		}
	}
}

void WorldMap::CheckDeathFighters()
{
	mSceneGraph.removeWrecks();
}

void WorldMap::buildLevelMap()
{
	mTileMapInfo = initializeTileMapInfo();
	TileMapLoader loader;
	std::vector<Tile> tileMap = loader.LoadFile("./Media/Maps/map.csv", mTileMapInfo);
	mTileMap.load(tileMap, sf::Vector2u(32, 32), mTextures.get(Textures::TestTile));
	mWorldBounds = mTileMap.getWorldBounds();
}

void WorldMap::draw()
{
	mTarget.setView(mWorldView);
	mTarget.draw(mSceneGraph);
}

CommandQueue& WorldMap::getCommandQueue()
{
	return mCommandQueue;
}

std::vector<Fighter*> WorldMap::getFighters()
{
	return mFighters;
}

void WorldMap::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		int category = Category::NONE;
		SceneNode* layer(new SceneNode(category));
		mSceneLayers[i] = layer;

		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.get(Textures::TestSky);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	SpriteNode* backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
	
	sf::Texture& textureFloor = mTextures.get(Textures::TestFloor);
	sf::IntRect textureRectFloor(0, 0, (int)(mWorldBounds.width), (int)(mWorldBounds.height/2.f));
	textureFloor.setRepeated(true);

	mSceneLayers[Floor]->attachChild(std::move(&mTileMap));

	mFighterInfo = initializeFighterData();
	sf::Vector2f spawnPosition(10, 608);
	Fighter* fighter = new Fighter(Fighter::Type::Warrior, mTextures, 0, spawnPosition, 100, mFighterInfo);
	mPlayer = fighter;
	mPlayer->setPosition(spawnPosition);
	mSceneLayers[ActionLayer]->attachChild(std::move(fighter));
	mFighters.push_back(fighter);

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			Fighter* enemy = new Fighter(Fighter::Type::Enemy, mTextures, j * i + 1 , sf::Vector2f(mWorldBounds.width / 2.f - 200 + j * 100, mWorldBounds.height / 2.f + i * 100), 100, mFighterInfo);
			enemy->setPosition(enemy->getWorldPosition());
			mSceneLayers[ActionLayer]->attachChild(std::move(enemy));
			mFighters.push_back(enemy);
		}
	}
}

void WorldMap::loadTextures()
{
	mTextures.load(Textures::TestSky, "Media/Textures/SkyTest.png");
	mTextures.load(Textures::TestFloor, "Media/Textures/FloorTest.png");
	mTextures.load(Textures::TestTile, "Media/Textures/tileTest.png");
	mTextures.load(Textures::TestFighter, "Media/Sprites/catFighterSprite.png");
	mTextures.load(Textures::TestWarrior, "Media/Sprites/advnt_full.png");
}
