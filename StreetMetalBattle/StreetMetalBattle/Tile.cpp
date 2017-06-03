#include "Tile.h"
#include <iostream>

Tile::Tile(int tileType, bool canWalkOver, sf::Vector2u position)
	: mTileType(tileType)
	, mCanWalkOver(canWalkOver)
	, mPosition(position)
{
}

sf::Vector2u Tile::getPosition() const
{
	return mPosition;
}

int Tile::getTileNumber() const
{
	return mTileType;
}

bool Tile::canWalk() const
{
	return mCanWalkOver;
}