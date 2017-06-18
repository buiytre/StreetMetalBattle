#include "World/Scenario/TileMapLoader.h"
#include <sstream>
#include <fstream>
#include <iostream>

std::vector<Tile> TileMapLoader::LoadFile(std::string file)
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
					Tile tile(typeTile, true, sf::Vector2u(x, y));
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
