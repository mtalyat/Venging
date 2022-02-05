#ifndef SCENE_H
#define SCENE_H

#include <cstdbool>
#include <glm/glm.hpp>
#include "System.h"
#include "List.h"
#include "Object.h"
#include "Window.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
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
	void instantiate(Entity* e, glm::vec3 position);
	/// <summary>
	/// Creates a new clone of the given entity in the Scene at the given position, with the given parent Transform.
	/// </summary>
	/// <param name="e"></param>
	void instantiate(Entity* e, glm::vec3 position, TransformComponent* parent);

	/// <summary>
	/// Adds a system to this Scene.
	/// </summary>
	/// <param name="system"></param>
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

	RenderingSystem* renderSystem;

	List<System*> systems;
	List<Entity*> entities;
};

#endif
