#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstdbool>
#include "Entity.h"
#include "List.h"
#include "Object.h"
#include "Component.h"
#include "Console.h"

/// <summary>
/// A System provides functionality to Entities, using their Components to read and store data.
/// </summary>
class System :
	public Object
{
public:
	System();

	/// <summary>
	/// Adds a Component to this System.
	/// </summary>
	/// <param name="e"></param>
	virtual void addEntity(Entity* entity);
	/// <summary>
	/// Removes a Component from this System.
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	virtual bool removeEntity(Entity* entity);

	/// <summary>
	/// Called when the System is initialized after it has been created, or once the Scene has initialized.
	/// </summary>
	virtual void init();
	/// <summary>
	/// Called when the System is started, which is after initialization.
	/// </summary>
	virtual void start();
	/// <summary>
	/// Called after the System has been started, and the Scene is running.
	/// </summary>
	virtual void update();
	/// <summary>
	/// Called during a fixed interval for physics.
	/// </summary>
	virtual void fixedUpdate();

	/// <summary>
	/// Initializes one Entity during the initialization of this System.
	/// </summary>
	/// <param name="index"></param>
	virtual void initEntity(const int index);
	/// <summary>
	/// Starts one Entity during the start of this System.
	/// </summary>
	/// <param name="index"></param>
	virtual void startEntity(const int index);
	/// <summary>
	/// Updates one Entity during the update loop, unless update is defined as otherwise.
	/// </summary>
	/// <param name="index"></param>
	virtual void updateEntity(const int index);
	/// <summary>
	/// Updates one Entity during the fixed update loop, unless fixedUpdate is defined as otherwise.
	/// </summary>
	/// <param name="index"></param>
	virtual void fixedUpdateEntity(const int index);

protected:
	List<Entity*> entities;
};

#endif
