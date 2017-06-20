#include "World/Scenario/TileMapLoader.h"
#include <sstream>
#include <fstream>

std::vector<Tile> TileMapLoader::LoadFile(std::string file, std::vector<TileMapInfo>& tileMapInfo)
{
	std::ifstream csvFileMap;
	csvFileMap.open(file, std::ios::in);
	std::string line;
	std::vector<Tile> vTile;
	if (csvFileMap.is_open())
	{
		int y = 0;
		while (std::getline(csvFileMap, line))
		{
			int x = 0;
			std::istringstream iss(line);
			std::string tile;
			while (std::getline(iss, tile, ','))
			{
				int typeTile = std::atoi(tile.c_str());
				if (typeTile != -1) 
				{
					TileMapInfo tileInfo = tileMapInfo[typeTile];
					Tile tile(typeTile, tileInfo.walkArea, sf::Vector2u(x, y));
					vTile.push_back(tile);
				}
				else
				{
					Tile tile(typeTile, false, sf::Vector2u(x, y));
					vTile.push_back(tile);
				}
				x++;
			}
			y++;
		}
	}
	csvFileMap.close();
	return vTile;
}
