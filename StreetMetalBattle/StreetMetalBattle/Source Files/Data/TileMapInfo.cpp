#include "Data/TileMapInfo.h"
const int MapSize = 667;

std::vector<TileMapInfo> initializeTileMapInfo()
{
	std::vector<TileMapInfo> tileMapInfo(MapSize);
	std::vector<int> walkablesTiles{23, 24, 25, 46, 47, 48, 69, 70, 71, 118, 119, 120, 141, 142, 143, 149, 150, 164, 165, 166, 172, 173, 218, 219, 241, 242 };
	for (int i = 0; i < MapSize; i++) 
	{
		TileMapInfo info;
		info.numTile = i;
		if (std::find(walkablesTiles.begin(), walkablesTiles.end(), i) != walkablesTiles.end())
		{
			info.walkArea = true;
		}

		tileMapInfo[i] = info;
	}
	return tileMapInfo;
}
