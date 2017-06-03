#pragma once
#include "World/WorldMap.h"

class AiController
{
	public:
		AiController(WorldMap* worldMap);
		void makeDecissions();

	private:
		WorldMap* mWorldMap;
};