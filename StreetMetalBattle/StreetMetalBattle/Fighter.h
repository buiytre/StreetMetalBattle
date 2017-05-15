#pragma once
#include "SceneNode.h"
#include "ResourceHolder.h"
#include "Animation.h"

class Fighter : public SceneNode
{
	public:
		explicit Fighter(const TextureHolder& textures);

	private:
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		Animation mNothing;
};