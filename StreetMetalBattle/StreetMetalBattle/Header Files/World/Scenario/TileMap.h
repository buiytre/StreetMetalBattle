#pragma once
#include <SFML/Graphics.hpp>
#include "SceneNode.h"
#include "Tile.h"

class TileMap : public SceneNode
{
	public:
		void load(std::vector<Tile> tiles, sf::Vector2u tileSize, sf::Texture texture);
		bool canWalk(sf::Vector2f position);
	
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	private:
		std::vector<Tile> mTiles;
		sf::VertexArray m_vertices;
		sf::Texture mTexture;
		sf::Vector2u mTileSize;
};