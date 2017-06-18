#pragma once
#include <string>
#include "World/Scenario/Tile.h"

class TileMapLoader
{
	public:

	std::vector<Tile> LoadFile(std::string file);
};