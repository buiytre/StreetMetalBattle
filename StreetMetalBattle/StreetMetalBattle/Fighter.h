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
		explicit Fighter(Type type, const TextureHolder & textures, sf::Int32 fighterId, sf::Vector2f position, sf::Int16 hitPoints);
		
		sf::Vector2f getWorldPosition() const;
		sf::Vector2f getWantToWalkPosition() const;
		void setPosition(const sf::Vector2f& position);
		void setWantToWalkPosition(const sf::Vector2f& position);

		bool isHitting();

		void goToStandBy();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void punch();
		void getHit(CommandQueue & commands, sf::Int16 damage);

		virtual bool isMarkedForRemoval() const;

		sf::FloatRect getBoundingRect() const;
		sf::FloatRect getPunchBoundingRect() const;

		unsigned int getCategory() const;

		sf::Int32 getIdentifier();
		void setIdentifier(sf::Int32 identifier);

	private:
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void handleInput(int input);
				

	private:
		virtual bool isDestroyed() const;
		void drawBoundingPunch(sf::RenderTarget & target, sf::RenderStates states) const;

	private:
		Type mType;
		FighterState* mState;

		Command mGetHitCommand;

		sf::Vector2f mPosition;
		sf::Vector2f mWantToWalk;
		sf::Int32 mHitPoints;
		const TextureHolder& mTextures;

		sf::Int32 mFighterId;
};