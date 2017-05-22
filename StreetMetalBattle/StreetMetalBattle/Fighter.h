#pragma once
#include "SceneNode.h"
#include "ResourceHolder.h"
#include "Animation.h"

class Fighter : public SceneNode
{
	public:
		enum Type
		{
			Player,
			Enemy,
			TypeCount,
		};

	public:
		explicit Fighter(Type type, const TextureHolder & textures, sf::Vector2f position);
		sf::Vector2f getWorldPosition() const;
		void setPosition(const sf::Vector2f& position);

		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void punch();

	private:
		enum Direction
		{
			Left,
			Right,
			Up,
			Down,
		};
		enum LastAction
		{
			Moving,
			Stand,
			Punch,
			None
		};

	private:
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		unsigned int getCategory() const;
	private:
		void updateAnimation(sf::Time dt);
		void setStandByAnimation();
		void setWalkingAnimation();
		void setPunchingAnimation();
		sf::FloatRect getBoundingRect() const;

	private:
		Type mType;
		Animation mFighterAnimation;
		Direction mOrientation;
		sf::Vector2f mVelocity;
		sf::Vector2f mPosition;
		LastAction mLastAction;
		bool mPunching;
		sf::Time timeLastPunch;
};