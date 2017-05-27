#pragma once
#include "SceneNode.h"
#include "ResourceHolder.h"
#include "Animation.h"
#include "FighterState.h"

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
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void handleInput(int input);

		unsigned int getCategory() const;

	private:
		virtual bool isDestroyed() const;
		void drawBoundingPunch(sf::RenderTarget & target, sf::RenderStates states) const;

	private:
		Type mType;
		FighterState* mState;

		sf::Vector2f mPosition;
		sf::Int32 mHitPoints;
		const TextureHolder& mTextures;
};