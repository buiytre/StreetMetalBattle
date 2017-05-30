#include "AiController.h"
#include "Category.h"
#include <random>
#include <time.h>

struct FighterRandomMover
{
	FighterRandomMover(int identifier)
		: fighterID(identifier)
	{
	}

	void operator() (Fighter& fighter, sf::Time) const
	{
		srand(time(NULL));
		if (fighter.getIdentifier() == fighterID)
		{
			int i = rand() % 3 + 1;
			if (i == 1) 
			{
				fighter.moveDown();
			}
			else if (i == 2)
			{
				fighter.moveUp();
			}

			i = rand() % 3 + 1;
			if (i == 1)
			{
				fighter.moveLeft();
			}
			else if (i == 2)
			{
				fighter.moveRight();
			}


			i = rand() % 2 + 1;
			if (i == 1)
			{
				fighter.punch();
			}
		}
	}
	int fighterID;
};

AiController::AiController(WorldMap* worldMap)
	: mWorldMap(worldMap)
{
}

void AiController::makeDecissions()
{
	CommandQueue& commands = mWorldMap->getCommandQueue();
	std::vector<Fighter*> fighters = mWorldMap->getFighters();
	for (Fighter* f : fighters)
	{
		Command command;
		command.category = Category::EnemyFighter;
		command.action = derivedAction<Fighter>(FighterRandomMover(f->getIdentifier()));
		commands.push(command);
	}
	
}
