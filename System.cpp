#include "System.h"

System::System() : Object()
{
	entities = List<Entity*>();
}

void System::addEntity(Entity* entity)
{
	entities.add(entity);
}

bool System::removeEntity(Entity* entity)
{
	return entities.remove(entity);
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
	for (; i < entities.length(); i++)
	{
		updateEntity(i);
	}
}

void System::fixedUpdate()
{
	int i = 0;
	for (; i < entities.length(); i++)
	{
		fixedUpdateEntity(i);
	}
}

void System::updateEntity(const int index)
{

}

void System::fixedUpdateEntity(const int index)
{

}
