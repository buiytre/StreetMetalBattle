#include <iostream>
#include "Game.h"

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	char c;
	std::cout << "Thanks for playing! Press any key to exit" << std::endl;
	std::cin >> c;
}