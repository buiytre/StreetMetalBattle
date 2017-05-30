#pragma once
#include "State.h"
#include "SFML\Graphics.hpp"
#include "WorldMap.h"
#include "AiController.h"

class GameState : State
{
	public:
		GameState(StateStack& stack, Context context);
	
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);

	private:
		WorldMap mWorld;
		Player& mPlayer;
		AiController mAiController;
};