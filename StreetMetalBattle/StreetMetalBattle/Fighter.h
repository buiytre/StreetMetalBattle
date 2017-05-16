#pragma once
#include "SceneNode.h"
#include "ResourceHolder.h"
#include "Animation.h"

class Fighter : public SceneNode
{
	public:
		explicit Fighter(const TextureHolder& textures);

		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();

	private:
		enum Direction
		{
			Left,
			Right,
			Up,
			Down,
		};

	private:
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		unsigned int getCategory() const;
	private:
		void updateAnimation(sf::Time dt);
		void setStandByAnimation();
		void setWalkingAnimation();

	private:
		Animation mFighterAnimation;
		Direction mOrientation;
		sf::Vector2f mVelocity;
		bool mLastActionMoving;
};