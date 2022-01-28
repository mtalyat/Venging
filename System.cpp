#include "System.h"

System::System() : Object()
{
	components = List<Component*>();
}

void System::addComponent(Component* component)
{
	components.add(component);
}

bool System::removeComponent(Component* component)
{
	return components.remove(component);
}

void System::init()
{

}

void System::start()
{

}

void System::update()
{
	int i = 0;
	for (; i < components.length(); i++)
	{
		updateEntity(components[i]);
	}
}

void System::fixedUpdate()
{
	int i = 0;
	for (; i < components.length(); i++)
	{
		fixedUpdateEntity(components[i]);
	}
}

void System::updateEntity(Component* component)
{
	
}

void System::fixedUpdateEntity(Component* component)
{

}
