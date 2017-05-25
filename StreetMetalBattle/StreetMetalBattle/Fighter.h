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
		explicit Fighter(Type type, const TextureHolder & textures, sf::Vector2f position, sf::Int16 hitPoints);
		sf::Vector2f getWorldPosition() const;
		void setPosition(const sf::Vector2f& position);

		bool isHitting();

		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void punch();
		void getHit(sf::Int16 damage);

		virtual bool isMarkedForRemoval() const;

		sf::FloatRect getBoundingRect() const;
		sf::FloatRect getPunchBoundingRect() const;

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
			PunchCombo,
			BeingPunched,
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
		void setBeingPunchedAnimation();
		void setDyingAnimation();

		virtual bool isDestroyed() const;


		void drawBoundingPunch(sf::RenderTarget & target, sf::RenderStates states) const;

	private:
		Type mType;
		Animation mFighterAnimation;
		Direction mOrientation;
		sf::Vector2f mVelocity;
		sf::Vector2f mPosition;
		LastAction mLastAction;
		bool mPunching;
		bool mPunchingCombo;
		bool mBeingPunched;
		bool mIsDying;
		sf::Time mTimeLastPunch;
		sf::Int32 mHitPoints;
};