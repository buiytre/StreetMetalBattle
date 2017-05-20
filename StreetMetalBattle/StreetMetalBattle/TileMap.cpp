#include "TileMap.h"
#include "Textures.h"
#include "SpriteNode.h"
#include "Category.h"
#include <algorithm>


TileMap::TileMap(sf::RenderWindow & window, FontHolder& fonts)
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
		mWorldView.getSize().x / 2.f, // x
		mWorldBounds.height - mWorldView.getSize().y / 2.f) //y
{
	mWorldView.setCenter(mWorldView.getSize()/2.f);
	loadTextures();
	buildScene();
}

void TileMap::update(sf::Time dt)
{
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}

	mSceneGraph.update(dt, mCommandQueue);
	mWorldView.setCenter(mPlayer->getWorldPosition());
	CheckPlayerInsideZone();
}

void TileMap::CheckPlayerInsideZone()
{
	
	sf::FloatRect worldBounds(mWorldBounds.left,mWorldBounds.top, mWorldBounds.width, mWorldBounds.height);
	const float borderDistance = 60.f;
	sf::Vector2f position = mPlayer->getPosition();
	position.x = std::max(position.x, worldBounds.left + borderDistance / 2);
	position.x = std::min(position.x, worldBounds.left + worldBounds.width - borderDistance / 2);
	position.y = std::max(position.y, worldBounds.top + mWorldBounds.height / 2.f);
	position.y = std::min(position.y, worldBounds.top + worldBounds.height - borderDistance);
	mPlayer->setPosition(position);
}

void TileMap::draw()
{
	mTarget.setView(mWorldView);
	mTarget.draw(mSceneGraph);
}

CommandQueue& TileMap::getCommandQueue()
{
	return mCommandQueue;
}

void TileMap::buildScene()
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

	std::unique_ptr<Fighter> fighter(new Fighter(mTextures));
	mPlayer = fighter.get();
	mPlayer->setPosition(mSpawnPosition);
	mSceneLayers[ActionLayer]->attachChild(std::move(fighter));
}

void TileMap::loadTextures()
{
	mTextures.load(Textures::TestSky, "Media/Textures/SkyTest.png");
	mTextures.load(Textures::TestFloor, "Media/Textures/FloorTest.png");
	mTextures.load(Textures::TestFighter, "Media/Sprites/catFighterSprite.png");
}
