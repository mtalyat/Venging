#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstdbool>
#include "Entity.h"
#include "List.h"
#include "Object.h"
#include "Component.h"

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
	void addComponent(Component* component);
	/// <summary>
	/// Removes a Component from this System.
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	bool removeComponent(Component* component);

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

protected:
	/// <summary>
	/// Called for each Component in the System during the Update loop, unless Update is defined otherwise.
	/// </summary>
	/// <param name="entity"></param>
	virtual void updateEntity(Component* component);
	/// <summary>
	/// Called for each Component in the System during the Fixed Update loop, unless Fixed Update is defined otherwise.
	/// </summary>
	/// <param name="component"></param>
	virtual void fixedUpdateEntity(Component* component);

private:
	List<Component*> components;
};

#endif
