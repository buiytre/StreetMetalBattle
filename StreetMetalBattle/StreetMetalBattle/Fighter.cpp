#include "Fighter.h"
#include "Utility.h"
#include "Textures.h"

namespace {
	const int texture = Textures::TestFighter;
	const sf::IntRect textureRect(0, 0, 64, 64);
}

Fighter::Fighter(const TextureHolder & textures)
	:	mNothing(textures.get(texture))
{
	mNothing.setFrameSize(sf::Vector2i(textureRect.width, textureRect.height));
	mNothing.setNumFrames(4);
	mNothing.setRepeating(true);

	mNothing.setDuration(sf::seconds(1));
	
	centerOrigin(mNothing);
}

void Fighter::updateCurrent(sf::Time dt, CommandQueue & commands)
{
	mNothing.update(dt);
}

void Fighter::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mNothing, states);
}
