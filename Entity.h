#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <cstddef>
#include "Component.h"
#include "List.h"
#include "Object.h"

class Transform;

/// <summary>
/// An object that exists within a Scene. Entities can hold components to store extra data.
/// </summary>
class Entity :
	public Object
{
public:
	/// <summary>
	/// Creates an empty Entity.
	/// </summary>
	Entity();
	~Entity();

	/// <summary>
	/// Gets the Transform for this Entity.
	/// </summary>
	/// <returns></returns>
	Transform* transform();

	/// <summary>
	/// Adds a Component to this Entity.
	/// </summary>
	/// <param name="comp"></param>
	void addComponent(Component* comp);
protected:
	std::string name;
	Transform* transformPtr;

private:
	List<Component*> components;
};

#endif
