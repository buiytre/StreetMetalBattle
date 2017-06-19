#pragma once
#include <vector>

struct TileMapInfo
{
	int numTile = 0;
	bool walkArea = false;
};

std::vector<TileMapInfo> initializeTileMapInfo();