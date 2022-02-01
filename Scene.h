#ifndef SCENE_H
#define SCENE_H

#include <cstdbool>
#include "System.h"
#include "Vector3.h"
#include "List.h"
#include "Object.h"
#include "Window.h"
#include "Transform.h"
#include "Camera.h"
#include "ColorPalette.h"
#include "Color.h"
#include "RenderingSystem.h"

/// <summary>
/// The Scene class regulates all of the Entities, Components and Systems within the Scene.
/// </summary>
class Scene :
	public Object
{
public:
	/// <summary>
	/// Creates an empty Scene.
	/// </summary>
	Scene();
	~Scene();

	/// <summary>
	/// Creates a new clone of the given entity in the Scene at the origin.
	/// </summary>
	/// <param name="e"></param>
	void instantiate(Entity* e);
	/// <summary>
	/// Creates a new clone of the given entity in the Scene at the given position.
	/// </summary>
	/// <param name="e"></param>
	void instantiate(Entity* e, Vector3 position);
	/// <summary>
	/// Creates a new clone of the given entity in the Scene at the given position, with the given parent Transform.
	/// </summary>
	/// <param name="e"></param>
	void instantiate(Entity* e, Vector3 position, Transform* parent);

	void addSystem(System* system);

	/// <summary>
	/// Initialized all Systems within the scene.
	/// </summary>
	void init();
	/// <summary>
	/// Starts all Systems within the scene.
	/// </summary>
	void start();
	/// <summary>
	/// Updates all Systems within the scene.
	/// </summary>
	void update();
	/// <summary>
	/// Fixed updates all Systems within the scene.
	/// </summary>
	void fixedUpdate();

	/// <summary>
	/// Stops the Scene and closes everything within the scene.
	/// </summary>
	void stop();

	/// <summary>
	/// Renders the Scene to the given Window.
	/// </summary>
	/// <param name="window"></param>
	void render(Window* window);
private:
	bool isInitialized;
	bool isStarted;

	ColorPalette palette;

	RenderingSystem* renderSystem;

	List<System*> systems;
	List<Entity*> entities;
};

#endif
