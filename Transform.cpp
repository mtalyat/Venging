#include "Transform.h"
#include "Entity.h"

Transform::Transform()
{
	init();
}

Transform::Transform(Entity& entityRef) : Component(entityRef)
{
	init();
}

Transform::Transform(const Transform& other)
{
	localPosition = other.localPosition;
	localScale = other.localScale;
	parent = other.parent;
	children = other.children;
}

glm::vec3 Transform::getPosition()
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

void Transform::setPosition(glm::vec3 v)
{
	localPosition = v;
}

void Transform::movePosition(glm::vec3 v)
{
	setPosition(getPosition() + v);
}

glm::vec3 Transform::getLocalPosition()
{
	return localPosition;
}

void Transform::setLocalPosition(glm::vec3 v)
{
	localPosition = v;
}

glm::vec3 Transform::getScale()
{
	if (parent == nullptr)
	{
		return getLocalScale();
	}
	else {
		return parent->getScale() * getLocalScale();
	}
}

void Transform::setScale(glm::vec3 v)
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

glm::vec3 Transform::getLocalScale()
{
	return localScale;
}

void Transform::setLocalScale(glm::vec3 v)
{
	localScale = v;
}

Transform* Transform::getParent()
{
	return parent;
}

void Transform::setParent(Transform* transform)
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

Transform* Transform::getChild(int index)
{
	return children[index];
}

void Transform::init()
{
	localPosition = glm::vec3();
	localScale = glm::vec3(1, 1, 1);
	parent = nullptr;
}

void Transform::addChild(Transform* child)
{
	children.add(child);
}

bool Transform::removeChild(Transform* child)
{
	return children.remove(child);
}
