#include "Game.h"
#include "GameStates/TitleState.h"
#include "Identifiers/States.h"
#include "Identifiers/Fonts.h"
#include "GameStates/GameState.h"

const sf::Time  Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mWindow(sf::VideoMode(1024, 768), "States", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mMusic()
, mSounds()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic, mSounds))
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::TITLE, "Media/Fonts/Capture_it.ttf");

	registerStates();
	mStateStack.pushState(States::TITLE);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			if (mStateStack.isEmpty())
			{
				mWindow.close();

			}
		}

		render();
	}
}

void Game::registerStates()
{
	mStateStack.registerState<TitleState>(States::TITLE);
	mStateStack.registerState<GameState>(States::GAME);
}

void Game::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}

void Game::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Game::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}