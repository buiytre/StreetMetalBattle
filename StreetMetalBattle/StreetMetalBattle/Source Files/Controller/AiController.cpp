#include "Controller/AiController.h"
#include <random>
#include <time.h>
#include "Identifiers/Category.h"

struct FighterRandomMover
{
	FighterRandomMover(int identifier)
		: fighterID(identifier)
	{
	}

	void operator() (Fighter& fighter, sf::Time) const
	{
		srand(time(NULL) * fighterID);
		if (fighter.getIdentifier() == fighterID)
		{
			int i = rand() % 6;
			switch (i)
			{
				case 1:
				{
					fighter.moveDown();
					break;
				}
				case 2:
				{
					fighter.moveUp();
					break;
				}
				case 3:
				{
					fighter.moveLeft();
					break;
				}
				case 4:
				{
					fighter.moveRight();
					break;
				}
				case 5:
				{
					fighter.punch();
					break;
				}
				default:
					break;
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
