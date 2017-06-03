#pragma once
#include "SceneNode.h"

class Tile
{
	public:
		explicit Tile(int tileType, bool canWalkOver, sf::Vector2u position);

		sf::Vector2u getPosition() const;
		int getTileNumber() const;
		bool canWalk() const;

	private:
		int mTileType;
		bool mCanWalkOver;
		sf::Vector2u mPosition;
};