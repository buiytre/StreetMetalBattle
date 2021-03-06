#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include "Utility.h"

SceneNode::SceneNode(int category)
	: mChildren()
	, mParent(nullptr)
	, mDefaultCategory(category)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::deatachChild(const SceneNode & node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) -> bool { return p == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
	updateCurrent(dt, commands);
	std::sort(mChildren.begin(), mChildren.end(), [](const SceneNode* a, const SceneNode* b)
	{
		return a->getWorldPosition().y < b->getWorldPosition().y;
	});
	updateChildren(dt, commands);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent) 
	{
		transform = node->getTransform() * transform;
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory())
	{
		command.action(*this, dt);
	}
	
	for (const Ptr& child : mChildren)
	{
		child->onCommand(command, dt);
	}
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);

	// Draw bounding rectangle - disabled by default
	drawBoundingRect(target, states);

}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const Ptr& child : mChildren)
	{
		child->draw(target, states);
	}
}

void SceneNode::drawBoundingRect(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape background;
	background.setPosition(sf::Vector2f(rect.left, rect.top));
	background.setSize(sf::Vector2f(rect.width, rect.height));
	background.setFillColor(sf::Color(0, 255, 0, 50));
	background.setOutlineColor(sf::Color::Green);

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(background);
	target.draw(shape);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue & commands)
{
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue & commands)
{
	for (const Ptr& child : mChildren)
	{
		child->update(dt, commands);
	}
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

void SceneNode::checkNodeCollision(SceneNode & node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
	{
		collisionPairs.insert(std::minmax(this, &node));
	}
	for (Ptr& child : mChildren)
	{
		child->checkNodeCollision(node, collisionPairs);
	}
}

void SceneNode::checkSceneCollision(SceneNode & sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);

	for (Ptr& child : sceneGraph.mChildren)
	{
		checkSceneCollision(*child, collisionPairs);
	}
}

bool SceneNode::isDestroyed() const
{
	return false;
}

bool SceneNode::isMarkedForRemoval() const
{
	return isDestroyed();
}

void SceneNode::removeWrecks()
{
	auto wreckFieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckFieldBegin, mChildren.end());

	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

unsigned int SceneNode::getCategory() const
{
	return mDefaultCategory;
}

bool collision(const SceneNode & lhs, const SceneNode & rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}


float distance(const SceneNode& lhs, const SceneNode& rhs)
{
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}