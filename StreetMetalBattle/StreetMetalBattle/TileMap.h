#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "CommandQueue.h"

class TileMap : private sf::NonCopyable
{
	public:
		explicit TileMap(sf::RenderWindow & window, FontHolder& fonts);
		void update(sf::Time dt);
		void draw();

		CommandQueue& getCommandQueue();

	private:
		enum Layer
		{
			Background,
			Floor,
			LayerCount
		};

	private:
		void buildScene();
		void loadTextures();

	private:
		sf::RenderWindow& mTarget;
		sf::View mWorldView;
		TextureHolder mTextures;
		FontHolder& mFonts;
		SceneNode mSceneGraph;
		std::array<SceneNode*, LayerCount> mSceneLayers;

		sf::FloatRect mWorldBounds;
		CommandQueue mCommandQueue;
};