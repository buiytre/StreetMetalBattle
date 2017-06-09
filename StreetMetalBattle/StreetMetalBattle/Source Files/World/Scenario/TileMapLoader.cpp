#include "World/Scenario/TileMapLoader.h"
#include <iostream>

void TileMapLoader::load(std::vector<Tile> tiles, sf::Vector2u tileSize, sf::Texture texture)
{
	mTileSize = tileSize;
	mTiles = tiles;
	mTexture = texture;
	m_vertices.setPrimitiveType(sf::Quads);
	unsigned int maxX = 0;
	unsigned int maxY = 0;
	for (Tile t : mTiles)
	{
		sf::Vector2u position = t.getPosition();
		if (position.x > maxX)
		{
			maxX = position.x;
		}
		if (position.y > maxY)
		{
			maxY = position.y;
		}
	}

	m_vertices.resize((maxX + 1)* (maxY + 1) * 4);

	for (Tile t : mTiles)
	{
		sf::Vector2u position = t.getPosition();
		int tileNumber = t.getTileNumber();
		int tu = tileNumber % (mTexture.getSize().x / tileSize.x);
		int tv = tileNumber / (mTexture.getSize().x / tileSize.x);

		sf::Vertex* quad = &m_vertices[(position.x + position.y*(maxX + 1)) * 4];

		quad[0].position = sf::Vector2f(position.x * tileSize.x, position.y * tileSize.y);
		quad[1].position = sf::Vector2f((1 + position.x) * tileSize.x, position.y * tileSize.y);
		quad[2].position = sf::Vector2f((1 + position.x) * tileSize.x, (1 + position.y) *tileSize.y);
		quad[3].position = sf::Vector2f(position.x * tileSize.x, (1 + position.y) * tileSize.y);

		// define its 4 texture coordinates
		quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
		quad[1].texCoords = sf::Vector2f((tu + 1)* tileSize.x, tv * tileSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) *tileSize.y);
		quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
	}
}

bool TileMapLoader::canWalk(sf::Vector2f position)
{
	for (Tile t : mTiles)
	{
		sf::Vector2u tilePosition = t.getPosition();
		//tilePosition.x = tilePosition.x / 2.f;
		//tilePosition.y = tilePosition.y / 2.f;
		if (position.x >= (tilePosition.x * mTileSize.x) && position.x <= ((tilePosition.x + 1) * mTileSize.x))
		{
			if (position.y >= (tilePosition.y * mTileSize.y) && position.y <= ((tilePosition.y + 1) * mTileSize.y))
			{
				return t.canWalk();
			}
		}
	}
	return false;
}

void TileMapLoader::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &mTexture;

	// draw the vertex array
	target.draw(m_vertices, states);
	drawMapForm(target, states);
}

void TileMapLoader::drawMapForm(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (Tile t : mTiles)
	{
		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(t.getPosition().x * mTileSize.x, t.getPosition().y * mTileSize.y));
		shape.setSize(sf::Vector2f(mTileSize.x, mTileSize.y));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Yellow);
		shape.setOutlineThickness(1.f);
		target.draw(shape);
	}
}
