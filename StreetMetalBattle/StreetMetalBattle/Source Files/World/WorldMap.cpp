#include "World/WorldMap.h"
#include "Identifiers/Textures.h"
#include "Header Files/SpriteNode.h"
#include "Identifiers/Category.h"
#include <algorithm>
#include <iostream>
#include "Header Files/Utility.h"


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
	buildLevelMap();
	buildScene();
}

void WorldMap::update(sf::Time dt)
{
	while (!mCommandQueue.isEmpty())
	{
		Command command = mCommandQueue.pop();
		mSceneGraph.onCommand(command, dt);
		for (Fighter* f : mFighters)
		{
			(*f).onCommand(command, dt);
		}
	}

	mSceneGraph.update(dt, mCommandQueue);

	for (Fighter* f : mFighters)
	{
		(*f).update(dt, mCommandQueue);
	}

	handleCollisions();
	CheckDeathFighters();
	mWorldView.setCenter(mPlayer->getWorldPosition());
	CheckFightersInsideZone();
}

void WorldMap::CheckFightersInsideZone()
{
	for (Fighter* f : mFighters)
	{
		sf::Vector2f position = (*f).getWantToWalkPosition();
		
		if (mTileMap.canWalk(position))
		{
			(*f).setPosition(position);
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
						(*mFighters[j]).setPosition(unitVector(fighterTwo - fighterOne) + fighterTwo);
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
						(*mFighters[j]).setPosition(unitVector(fighterTwo - fighterOne)*2.f + fighterTwo);
					}
				}
			}
		}
	}
}

void WorldMap::CheckDeathFighters()
{
	mFighters.erase(std::remove_if(mFighters.begin(), mFighters.end(), [&](const Fighter* f) { return (*f).isMarkedForRemoval(); }), mFighters.end());
}

void WorldMap::buildLevelMap()
{
	std::vector<Tile> tiles;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 1; j < 20; j++)
		{
			tiles.push_back(Tile(0, true, sf::Vector2u(i, j)));
		}
		for (int j = 20; j < 30; j++)
		{
			tiles.push_back(Tile(1, true, sf::Vector2u(i, j)));
		}
		for (int j = 30; j < 40; j++)
		{
			tiles.push_back(Tile(2, false, sf::Vector2u(i, j)));
		}
	}

	for (int i = 10; i < 40; i++)
	{
		for (int j = 15; j < 30; j++)
		{
			tiles.push_back(Tile(1, true, sf::Vector2u(i, j)));
		}	
	}
	
	mTileMap.load(tiles, sf::Vector2u(32,32), mTextures.get(Textures::TestFloor));
}

void WorldMap::draw()
{
	mTarget.setView(mWorldView);
	mTarget.draw(mSceneGraph);
	mTarget.draw(mTileMap);
	std::sort(mFighters.begin(), mFighters.end(), [](Fighter* a, Fighter* b)
	{
		return a->getWorldPosition().y < b->getWorldPosition().y;
	});
	for (Fighter* f : mFighters)
	{
		mTarget.draw(*f);
	}
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
		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.get(Textures::TestSky);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
	
	sf::Texture& textureFloor = mTextures.get(Textures::TestFloor);
	sf::IntRect textureRectFloor(0, 0, (int)(mWorldBounds.width), (int)(mWorldBounds.height/2.f));
	textureFloor.setRepeated(true);

	std::unique_ptr<SpriteNode> floorSprite(new SpriteNode(textureFloor, textureRectFloor));
	floorSprite->setPosition(mWorldBounds.left, mWorldBounds.height/2.f);
	mSceneLayers[Floor]->attachChild(std::move(floorSprite));
	
	Fighter* fighter = new Fighter(Fighter::Type::Player, mTextures, 0, mSpawnPosition, 100);
	mPlayer = fighter;
	mPlayer->setPosition(mSpawnPosition);
	mFighters.push_back(fighter);

	Fighter* enemy = new Fighter(Fighter::Type::Enemy, mTextures, 1, sf::Vector2f(mWorldBounds.width / 2.f, mWorldBounds.height / 2.f + 100), 100);
	enemy->setPosition(enemy->getWorldPosition());
	mFighters.push_back(enemy);
}

void WorldMap::loadTextures()
{
	mTextures.load(Textures::TestSky, "Media/Textures/SkyTest.png");
	mTextures.load(Textures::TestFloor, "Media/Textures/FloorTest.png");
	mTextures.load(Textures::TestFighter, "Media/Sprites/catFighterSprite.png");
}
