#include "Utility.h"
#include <cassert>
#include <random>
#include <SFML\Graphics.hpp>


namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}


std::string toString(sf::Keyboard::Key key)
{
#define KEYTOSTRING(KEY) case sf::Keyboard::KEY: return #KEY;

	switch (key)
	{
		KEYTOSTRING(Unknown)
			KEYTOSTRING(A)
			KEYTOSTRING(B)
			KEYTOSTRING(C)
			KEYTOSTRING(D)
			KEYTOSTRING(E)
			KEYTOSTRING(F)
			KEYTOSTRING(G)
			KEYTOSTRING(H)
			KEYTOSTRING(I)
			KEYTOSTRING(J)
			KEYTOSTRING(K)
			KEYTOSTRING(L)
			KEYTOSTRING(M)
			KEYTOSTRING(N)
			KEYTOSTRING(O)
			KEYTOSTRING(P)
			KEYTOSTRING(Q)
			KEYTOSTRING(R)
			KEYTOSTRING(S)
			KEYTOSTRING(T)
			KEYTOSTRING(U)
			KEYTOSTRING(V)
			KEYTOSTRING(W)
			KEYTOSTRING(X)
			KEYTOSTRING(Y)
			KEYTOSTRING(Z)
			KEYTOSTRING(Num0)
			KEYTOSTRING(Num1)
			KEYTOSTRING(Num2)
			KEYTOSTRING(Num3)
			KEYTOSTRING(Num4)
			KEYTOSTRING(Num5)
			KEYTOSTRING(Num6)
			KEYTOSTRING(Num7)
			KEYTOSTRING(Num8)
			KEYTOSTRING(Num9)
			KEYTOSTRING(Escape)
			KEYTOSTRING(LControl)
			KEYTOSTRING(LShift)
			KEYTOSTRING(LAlt)
			KEYTOSTRING(LSystem)
			KEYTOSTRING(RControl)
			KEYTOSTRING(RShift)
			KEYTOSTRING(RAlt)
			KEYTOSTRING(RSystem)
			KEYTOSTRING(Menu)
			KEYTOSTRING(LBracket)
			KEYTOSTRING(RBracket)
			KEYTOSTRING(SemiColon)
			KEYTOSTRING(Comma)
			KEYTOSTRING(Period)
			KEYTOSTRING(Quote)
			KEYTOSTRING(Slash)
			KEYTOSTRING(BackSlash)
			KEYTOSTRING(Tilde)
			KEYTOSTRING(Equal)
			KEYTOSTRING(Dash)
			KEYTOSTRING(Space)
			KEYTOSTRING(Return)
			KEYTOSTRING(BackSpace)
			KEYTOSTRING(Tab)
			KEYTOSTRING(PageUp)
			KEYTOSTRING(PageDown)
			KEYTOSTRING(End)
			KEYTOSTRING(Home)
			KEYTOSTRING(Insert)
			KEYTOSTRING(Delete)
			KEYTOSTRING(Add)
			KEYTOSTRING(Subtract)
			KEYTOSTRING(Multiply)
			KEYTOSTRING(Divide)
			KEYTOSTRING(Left)
			KEYTOSTRING(Right)
			KEYTOSTRING(Up)
			KEYTOSTRING(Down)
			KEYTOSTRING(Numpad0)
			KEYTOSTRING(Numpad1)
			KEYTOSTRING(Numpad2)
			KEYTOSTRING(Numpad3)
			KEYTOSTRING(Numpad4)
			KEYTOSTRING(Numpad5)
			KEYTOSTRING(Numpad6)
			KEYTOSTRING(Numpad7)
			KEYTOSTRING(Numpad8)
			KEYTOSTRING(Numpad9)
			KEYTOSTRING(F1)
			KEYTOSTRING(F2)
			KEYTOSTRING(F3)
			KEYTOSTRING(F4)
			KEYTOSTRING(F5)
			KEYTOSTRING(F6)
			KEYTOSTRING(F7)
			KEYTOSTRING(F8)
			KEYTOSTRING(F9)
			KEYTOSTRING(F10)
			KEYTOSTRING(F11)
			KEYTOSTRING(F12)
			KEYTOSTRING(F13)
			KEYTOSTRING(F14)
			KEYTOSTRING(F15)
			KEYTOSTRING(Pause)
	}

	return "";
}
float toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}

void centerOrigin(sf::Sprite & sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text & text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(Animation& animation)
{
	sf::FloatRect bounds = animation.getLocalBounds();
	animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerBottom(sf::Sprite & sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height));
}

void centerBottom(sf::Text & text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height));
}


void centerBottom(Animation& animation)
{
	sf::FloatRect bounds = animation.getLocalBounds();
	animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height));
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / length(vector);
}

int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}
