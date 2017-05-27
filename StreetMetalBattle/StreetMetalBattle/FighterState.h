#pragma once
#include "SFML\Graphics.hpp"
#include "Textures.h"
#include "Inputs.h"

class Fighter;
class CommandQueue;
namespace {
	const int texture = Textures::TestFighter;
	const sf::IntRect textureRect(0, 0, 64, 64);
	const int speed = 100;
}

class FighterState
{
	public:
		virtual ~FighterState() {}
		virtual FighterState* handleInput(Fighter& fighter, int input) { return nullptr; }
		virtual FighterState* update(Fighter& fighter, sf::Time dt, CommandQueue & commands) { return nullptr; }
		virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const {};
		virtual sf::FloatRect getBoundingRect() const { return sf::FloatRect(); };
		virtual sf::FloatRect getPunchBoundingRect() const { return sf::FloatRect(); };
		virtual bool isHitting() const { return false; };
		virtual bool end() const { return false; };
};