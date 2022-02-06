#include "TransformComponent.h"
#include "Entity.h"

glm::vec3 TransformComponent::up = glm::vec3(0.0f, 1.0f, 0.0f);

TransformComponent::TransformComponent()
{
	init();
}

TransformComponent::TransformComponent(Entity& entityRef) : Component(entityRef)
{
	init();
}

TransformComponent::TransformComponent(const TransformComponent& other)
{
	localPosition = other.localPosition;
	localScale = other.localScale;
	parent = other.parent;
	children = other.children;
}

glm::vec3 TransformComponent::getPosition()
{
	if (parent == nullptr)
	{
		return getLocalPosition();
	}
	else {
		//parent exists, so add local position to it
		return getLocalPosition() + parent->getPosition();
	}
}

void TransformComponent::setPosition(glm::vec3 v)
{
	localPosition = v;
}

void TransformComponent::movePosition(glm::vec3 v)
{
	setPosition(getPosition() + v);
}

glm::vec3 TransformComponent::getLocalPosition()
{
	return localPosition;
}

void TransformComponent::setLocalPosition(glm::vec3 v)
{
	localPosition = v;
}

glm::vec3 TransformComponent::getScale()
{
	if (parent == nullptr)
	{
		return getLocalScale();
	}
	else {
		return parent->getScale() * getLocalScale();
	}
}

void TransformComponent::setScale(glm::vec3 v)
{
	if (parent == nullptr)
	{
		setLocalScale(v);
	}
	else {
		//get parent scale
		glm::vec3 parentScale = parent->getScale();

		//scale this Transform so that the scale reflects the given value v in the world
		setLocalScale(v / parentScale);
	}
}

glm::vec3 TransformComponent::getLocalScale()
{
	return localScale;
}

void TransformComponent::setLocalScale(glm::vec3 v)
{
	localScale = v;
}

glm::vec3 TransformComponent::getRotation()
{
	if (parent == nullptr)
	{
		return getLocalRotation();
	}
	else
	{
		return parent->getRotation() + getLocalRotation();
	}
}

void TransformComponent::setRotation(glm::vec3 v)
{
	if (parent == nullptr)
	{
		setLocalRotation(v);
	}
	else
	{
		setLocalRotation(v - parent->getRotation());
	}
}

glm::vec3 TransformComponent::getLocalRotation()
{
	return localRotation;
}

void TransformComponent::setLocalRotation(glm::vec3 v)
{
	localRotation = v;
}

TransformComponent* TransformComponent::getParent()
{
	return parent;
}

void TransformComponent::setParent(TransformComponent* transform)
{
	//if there is a parent already, remove this from its children
	if (parent != nullptr)
	{
		parent->removeChild(this);
	}

	parent = transform;

	//if new parent is not null, add this to its children
	if (parent != nullptr)
	{
		parent->addChild(this);
	}
}

TransformComponent* TransformComponent::getChild(int index)
{
	return children[index];
}

void TransformComponent::init()
{
	localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	localScale = glm::vec3(1.0f, 1.0f, 1.0f);
	localRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	parent = nullptr;
}

void TransformComponent::addChild(TransformComponent* child)
{
	children.add(child);
}

bool TransformComponent::removeChild(TransformComponent* child)
{
	return children.remove(child);
}
