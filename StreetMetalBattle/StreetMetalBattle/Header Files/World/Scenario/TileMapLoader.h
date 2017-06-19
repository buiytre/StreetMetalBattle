#pragma once
#include <string>
#include "World/Scenario/Tile.h"
#include "Data/TileMapInfo.h"

class TileMapLoader
{
	public:

	std::vector<Tile> LoadFile(std::string file, std::vector<TileMapInfo>& tileMapInfo);
};