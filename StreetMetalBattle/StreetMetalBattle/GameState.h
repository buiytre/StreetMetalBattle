#pragma once
#include "State.h"
#include "SFML\Graphics.hpp"
#include "TileMap.h"

class GameState : State
{
	public:
		GameState(StateStack& stack, Context context);
	
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);

	private:
		TileMap mWorld;
		Player& mPlayer;
};