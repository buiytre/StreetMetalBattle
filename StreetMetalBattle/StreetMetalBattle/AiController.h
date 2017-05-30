#pragma once
#include "WorldMap.h"
#include "Fighter.h"

class AiController
{
	public:
		AiController(WorldMap* worldMap);
		void makeDecissions();

	private:
		WorldMap* mWorldMap;
};