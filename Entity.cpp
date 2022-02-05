#include "Entity.h"
#include "TransformComponent.h"

Entity::Entity()
{
	name = "";
	transformPtr = new TransformComponent();
}

Entity::~Entity()
{
	delete(transformPtr);
}

TransformComponent* Entity::transform()
{
	return transformPtr;
}

void Entity::addComponent(Component* comp)
{
	components.add(comp);
	comp->setEntity(this);
}
