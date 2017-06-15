#pragma once
#include <memory>
#include <vector>
#include <set>
#include <utility>
#include <SFML\Graphics.hpp>
#include "CommandQueue.h"
#include "Command.h"


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef SceneNode* Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

public:
	explicit SceneNode(int category = 0);

	void attachChild(Ptr child);
	Ptr deatachChild(const SceneNode& node);

	void update(sf::Time dt, CommandQueue& commands);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
	void onCommand(const Command& command, sf::Time dt);
	virtual sf::FloatRect getBoundingRect() const;
	void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	virtual bool isDestroyed() const;
	void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	virtual bool isMarkedForRemoval() const;
	void removeWrecks();
	virtual unsigned int getCategory() const;

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	void updateChildren(sf::Time dt, CommandQueue& commands);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;



private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
	int mDefaultCategory;
};

bool	collision(const SceneNode& lhs, const SceneNode& rhs);
float	distance(const SceneNode& lhs, const SceneNode& rhs);