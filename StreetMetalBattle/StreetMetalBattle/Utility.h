#pragma once
#include <sstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "Animation.h"

namespace sf
{
	class Sprite;
	class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);
float toDegree(float radian);
float toRadian(float degree);


void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(Animation& animation);
int randomInt(int exclusiveMax);

template<typename T>
inline std::string toString(const T & value)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}

float length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);