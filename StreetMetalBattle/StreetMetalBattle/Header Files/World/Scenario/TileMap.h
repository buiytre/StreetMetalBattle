#pragma once
#include <SFML/Graphics.hpp>
#include "SceneNode.h"
#include "Tile.h"

class TileMap : public SceneNode
{
	public:
		void load(std::vector<Tile> tiles, sf::Vector2u tileSize, sf::Texture texture);
		bool canWalk(sf::Vector2f position);
		sf::Vector3f canFall(sf::Vector2f fromPosition, sf::Vector2f toPosition);
		sf::FloatRect getWorldBounds();
	
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	private:
		std::vector<Tile> mTiles;
		sf::VertexArray m_vertices;
		sf::Texture mTexture;
		sf::Vector2u mTileSize;
		sf::FloatRect mWorldBounds;
};