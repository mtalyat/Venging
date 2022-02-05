#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <cstddef>
#include <typeinfo>
#include "Component.h"
#include "List.h"
#include "Object.h"

class TransformComponent;

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
	TransformComponent* transform();

	/// <summary>
	/// Adds a Component to this Entity.
	/// </summary>
	/// <param name="comp"></param>
	void addComponent(Component* comp);

	template <class T> T* getComponent();
protected:
	std::string name;
	TransformComponent* transformPtr;

private:
	List<Component*> components;
};

template<class T>
inline T* Entity::getComponent()
{
	//cycle through the components, if we find one that matches type, return it
	int i = 0;
	for (; i < components.length(); i++)
	{
		if (typeid(*components[i]) == typeid(T))
		{
			return (T*)(components[i]);
		}
	}

	//not found
	return NULL;
}

#endif


