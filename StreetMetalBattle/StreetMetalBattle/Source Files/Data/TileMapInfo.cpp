#include "Data/TileMapInfo.h"

std::vector<TileMapInfo> initializeTileMapInfo()
{
	std::vector<TileMapInfo> tileMapInfo;
	for (int i = 0; i <= 667; i++) 
	{
		TileMapInfo info;
		info.numTile = i;
		if (info.numTile == 23 || info.numTile == 24 || info.numTile == 25 
			|| info.numTile == 46 || info.numTile == 47 || info.numTile == 48 
			|| info.numTile == 69 || info.numTile == 70 || info.numTile == 71 
			|| info.numTile == 149 || info.numTile == 150 
			|| info.numTile == 218 || info.numTile == 219
			|| info.numTile == 118 || info.numTile == 119 || info.numTile == 120
			|| info.numTile == 141 || info.numTile == 142 || info.numTile == 143
			|| info.numTile == 164 || info.numTile == 165 || info.numTile == 166)
		{
			info.walkArea = true;
		}
		else 
		{
			info.walkArea = false;
		}
		tileMapInfo.push_back(info);
	}
	return tileMapInfo;
}
