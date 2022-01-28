#include "Entity.h"
#include "Transform.h"

Entity::Entity()
{
	name = "";
	transformPtr = new Transform();
}

Entity::~Entity()
{
	delete(transformPtr);
}

Transform* Entity::transform()
{
	return transformPtr;
}

void Entity::addComponent(Component* comp)
{
	components.add(comp);
	comp->setEntity(this);
}
