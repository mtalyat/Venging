#include "Component.h"
#include "Transform.h"
#include "Entity.h"

Component::Component()
{
	entityPtr = nullptr;
}

Component::Component(Entity& entityRef)
{
	entityPtr = &entityRef;
}

Entity* Component::entity()
{
	return entityPtr;
}

Transform* Component::transform()
{
	Entity* e = entity();

	if (e == nullptr) return nullptr;

	return e->transform();
}

void Component::setEntity(Entity* e)
{
	entityPtr = e;
}
