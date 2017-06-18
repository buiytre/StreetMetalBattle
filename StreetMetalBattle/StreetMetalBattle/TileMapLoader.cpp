#include "TileMapLoader.h"
#include <fstream>
#include <iostream>

std::vector<Tile> TileMapLoader::LoadFile(std::string file)
{
	std::ifstream csvFileMap;
	csvFileMap.open(file, std::ios::in);
	std::string line;
	if (csvFileMap.is_open())
	{
		while (std::getline(csvFileMap, line))
		{
			std::cout << line << std::endl;
		}
	}
	csvFileMap.close();
	return std::vector<Tile>();
}
