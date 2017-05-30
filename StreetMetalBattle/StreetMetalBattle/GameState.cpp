#include "GameState.h"
#include "CommandQueue.h"
#include "Player.h"

GameState::GameState(StateStack & stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.fonts)
	, mPlayer(*context.player)
	, mAiController(&mWorld)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);
	mAiController.makeDecissions();
	return true;
}

bool GameState::handleEvent(const sf::Event & event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}

	return true;
}
