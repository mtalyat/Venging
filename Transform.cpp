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

Vector3 Transform::getPosition()
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

void Transform::setPosition(Vector3 v)
{
	localPosition = v;
}

void Transform::movePosition(Vector3 v)
{
	setPosition(getPosition() + v);
}

Vector3 Transform::getLocalPosition()
{
	return localPosition;
}

void Transform::setLocalPosition(Vector3 v)
{
	localPosition = v;
}

Vector3 Transform::getScale()
{
	if (parent == nullptr)
	{
		return getLocalScale();
	}
	else {
		return parent->getScale() + getLocalScale();
	}
}

void Transform::setScale(Vector3 v)
{
	if (parent == nullptr)
	{
		setLocalScale(v);
	}
	else {
		//get parent scale
		Vector3 parentScale = parent->getScale();

		//scale this Transform so that the scale reflects the given value v in the world
		setLocalScale(v / parentScale);
	}
}

Vector3 Transform::getLocalScale()
{
	return localScale;
}

void Transform::setLocalScale(Vector3 v)
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
	localPosition = Vector3();
	localScale = Vector3::one();
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
