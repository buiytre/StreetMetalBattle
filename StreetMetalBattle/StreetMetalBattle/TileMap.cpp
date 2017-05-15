#include "TileMap.h"
#include "Textures.h"
#include "SpriteNode.h"
#include "Category.h"

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
	,mCommandQueue()
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
	sf::IntRect textureRectFloor(0.f, 0.f, mWorldBounds.width, mWorldBounds.height/2.f);
	textureFloor.setRepeated(true);

	std::unique_ptr<SpriteNode> floorSprite(new SpriteNode(textureFloor, textureRectFloor));
	floorSprite->setPosition(mWorldBounds.left, mWorldBounds.height/2.f);
	mSceneLayers[Floor]->attachChild(std::move(floorSprite));
}

void TileMap::loadTextures()
{
	mTextures.load(Textures::TestSky, "Media/Textures/SkyTest.png");
	mTextures.load(Textures::TestFloor, "Media/Textures/FloorTest.png");
}
