#include <chrono>
#include <ctime>
#include "Engine.h"
#include "Time.h"

Engine::Engine(Window* ww)
{
	running = false;
	workingWindow = ww;
	currentScene = nullptr;
	scenes = List<Scene*>();
}

Engine::~Engine()
{

}

void Engine::run()
{
	if (running)
	{
		Console::LogWarning("Attempted to run an already running Engine.");
		return;
	}
	else if (scenes.length() == 0)
	{
		Console::LogError("Attempted to run an Engine with no Scenes. Must call addScene(...) at least once before run().");
		return;
	}

	running = true;

	currentScene = scenes[0];

	GLFWwindow* window = workingWindow->glfwWindow();

	//initialize and start the scene
	currentScene->init();
	currentScene->start();

	//tell GL to check for depth
	glEnable(GL_DEPTH_TEST);

	//tell GL to only draw the front side
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//clock_t start = clock();
	//clock_t elapsed = clock();
	//clock_t now;
	auto start = std::chrono::system_clock::now();
	auto last = start;

	while (running && !glfwWindowShouldClose(window))
	{
		//start by clearing
		workingWindow->clear();

		//update the scene
		currentScene->update();

		//render the scene
		currentScene->render(workingWindow);

		//record time passed
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_seconds = now - last;
		std::chrono::duration<float> total_seconds = now - start;

		Time::deltaTime = elapsed_seconds.count();
		Time::timeSinceStartup = total_seconds.count();

		last = now;
	}
}

void Engine::quit()
{
	running = false;
}

void Engine::addScene(Scene* scene)
{
	scenes.add(scene);
}

bool Engine::isRunning()
{
	return running;
}
