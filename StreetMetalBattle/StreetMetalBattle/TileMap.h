#pragma once
#include <array>
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "Fighter.h"

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
			ActionLayer,
			LayerCount
		};

	private:
		void buildScene();
		void loadTextures();
		void CheckPlayerInsideZone();
		void handleCollisions();

	private:
		Fighter* mPlayer;

		sf::RenderWindow& mTarget;
		sf::View mWorldView;
		TextureHolder mTextures;
		FontHolder& mFonts;
		SceneNode mSceneGraph;
		std::array<SceneNode*, LayerCount> mSceneLayers;
		std::vector<Fighter*> mFighters;


		sf::FloatRect mWorldBounds;
		sf::Vector2f mSpawnPosition;
		CommandQueue mCommandQueue;
};