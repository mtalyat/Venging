#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"

class Entity;
class Transform;

/// <summary>
/// A generic Component that holds data for Entity objects.
/// </summary>
class Component :
	public Object
{
public:
	/// <summary>
	/// Creates an empty Component.
	/// </summary>
	Component();

	/// <summary>
	/// Creates a new Component that is on the given Entity.
	/// </summary>
	/// <param name="entityRef"></param>
	Component(Entity& entityRef);

	/// <summary>
	/// Gets the Entity that this Component is attached to.
	/// </summary>
	/// <returns></returns>
	Entity* entity();

	/// <summary>
	/// Gets the Transform that belongs to the Entity that this Component is on.
	/// </summary>
	/// <returns></returns>
	Transform* transform();

	/// <summary>
	/// Sets the Entity that this Component is attached to.
	/// </summary>
	/// <param name="e"></param>
	void setEntity(Entity* e);

protected:
	Entity* entityPtr;
};

#endif
