#ifndef ENGINE_H
#define ENGINE_H

#include <cstdbool>
#include <GLFW/glfw3.h>
#include "Console.h"
#include "Window.h"
#include "Scene.h"
#include "List.h"
#include "Object.h"
#include "ColorPalette.h"

class Window;
class Scene;

/// <summary>
/// Handles running the game, including the Window, game loop, scenes, and more.
/// </summary>
class Engine
	: public Object
{
public:
	/// <summary>
	/// Creates a new Engine, using the Window to render the Engine to.
	/// </summary>
	/// <param name="ww"></param>
	Engine(Window* ww);
	~Engine();

	/// <summary>
	/// Runs the Engine.
	/// </summary>
	void run();
	/// <summary>
	/// Stops the Engine, if it is currently running.
	/// </summary>
	void quit();

	/// <summary>
	/// Adds a Scene to the Engine.
	/// </summary>
	/// <param name="scene"></param>
	void addScene(Scene* scene);

	/// <summary>
	/// Determines if the Engine is running.
	/// </summary>
	/// <returns>True if the Engine is running, otherwise false.</returns>
	bool isRunning();
private:
	List<Scene*> scenes;
	Scene* currentScene;

	Window* workingWindow;
	bool running;
};

#endif