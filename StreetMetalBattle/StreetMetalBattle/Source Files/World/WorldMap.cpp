#include "World/WorldMap.h"
#include "Identifiers/Textures.h"
#include "SpriteNode.h"
#include "Identifiers/Category.h"
#include <algorithm>
#include <iostream>
#include "Utility.h"


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
	, mSpawnPosition(
		mWorldBounds.left+10, // x
		mWorldBounds.height - mWorldBounds.height / 2.f) //y
	, mTileMap()
{
	mWorldView.setCenter(mWorldView.getSize()/2.f);
	loadTextures();
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
	mWorldView.setCenter(mPlayer->getWorldPosition());
	CheckFightersInsideZone();
}

void WorldMap::CheckFightersInsideZone()
{
	for (Fighter* f : mFighters)
	{
		sf::Vector2f actualPosition = f->getPosition();
		sf::Vector2f wantToWalkTo = f->getWantToWalkPosition();
		std::cout << "Fighter " << f->getIdentifier() << " is on position (" << actualPosition.x << "," << actualPosition.y << ") and wants to walk to (" << wantToWalkTo.x << "," << wantToWalkTo.y << ")" << std::endl;

		if (mTileMap.canWalk(wantToWalkTo))
		{
			std::cout << "Fighter " << f->getIdentifier() << " can walk to position " << std::endl;
			(*f).setPosition(wantToWalkTo);
			continue;
		}
			
		sf::Vector2f positionX = sf::Vector2f(wantToWalkTo.x, actualPosition.y);
		if (mTileMap.canWalk(positionX))
		{
			std::cout << "Fighter " << f->getIdentifier() << " just move x" << std::endl;
			(*f).setPosition(positionX);
			continue;
		}

		sf::Vector2f positionY = sf::Vector2f(actualPosition.x, wantToWalkTo.y);
		if (mTileMap.canWalk(positionY)) 
		{
			std::cout << "Fighter " << f->getIdentifier() << " just move y" << std::endl;
			(*f).setPosition(positionY);
			continue;
		}	
		std::cout << "Fighter " << f->getIdentifier() << " can not walk to position" << std::endl;
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
	std::vector<Tile> tiles;
	tiles.push_back(Tile(23, true, sf::Vector2u(0, 1)));

	for (int x = 1; x < 40; x++)
	{
		tiles.push_back(Tile(24, true, sf::Vector2u(x, 1)));
	}

	tiles.push_back(Tile(25, true, sf::Vector2u(40, 1)));

	for (int y = 2; y < 24; y++) 
	{
		tiles.push_back(Tile(46, true, sf::Vector2u(0, y)));
	}

	tiles.push_back(Tile(69, true, sf::Vector2u(0, 24)));
	
	for (int x = 1; x < 40; x++)
	{
		tiles.push_back(Tile(70, true, sf::Vector2u(x, 24)));
	}

	tiles.push_back(Tile(71, true, sf::Vector2u(40, 24)));

	for (int y = 2; y < 24; y++)
	{
		tiles.push_back(Tile(48, true, sf::Vector2u(40, y)));
	}

	for (int x = 1; x < 30; x++)
	{
		for (int y = 2; y < 24; y++)
		{
			tiles.push_back(Tile(47, true, sf::Vector2u(x, y)));
		}
	}

	for (int x = 30; x < 40; x++)
	{
		for (int y = 2; y < 24; y++)
		{
			tiles.push_back(Tile(73, false, sf::Vector2u(x, y)));
		}
	}
	
	mTileMap.load(tiles, sf::Vector2u(32,32), mTextures.get(Textures::TestTile));
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

	buildLevelMap();
	mSceneLayers[Floor]->attachChild(std::move(&mTileMap));
	mFighterInfo = initializeFighterData();
	Fighter* fighter = new Fighter(Fighter::Type::Player, mTextures, 0, mSpawnPosition, 100, mFighterInfo);
	mPlayer = fighter;
	mPlayer->setPosition(mSpawnPosition);
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
}
