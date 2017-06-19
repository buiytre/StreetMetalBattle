#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "CommandQueue.h"
#include "Entities/Fighter.h"
#include  "Scenario/TileMap.h"
#include "Data/TileMapInfo.h"

class WorldMap : private sf::NonCopyable
{
	public:
		explicit WorldMap(sf::RenderWindow & window, FontHolder& fonts);
		void update(sf::Time dt);
		void draw();

		CommandQueue& getCommandQueue();
		std::vector<Fighter*> getFighters();

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
		void CheckFightersInsideZone();
		void handleCollisions();
		void CheckDeathFighters();
		void buildLevelMap();

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

		TileMap mTileMap;
		std::vector<FighterInfo> mFighterInfo;
		std::vector<TileMapInfo> mTileMapInfo;
};