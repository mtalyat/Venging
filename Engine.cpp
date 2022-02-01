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

	Stopwatch watch;
	watch.start();

	int frameCount = 0;
	float timer = 0.0f;
	int fps = 0;

	while (running && !glfwWindowShouldClose(window))
	{
		frameCount++;

		//start by clearing
		workingWindow->clear();

		//update the scene
		currentScene->update();

		//render the scene
		currentScene->render(workingWindow);

		//record time passed
		watch.lap();

		Time::deltaTime = watch.getLapTimeElapsed();
		Time::timeSinceStartup = watch.getTotalTimeElapsed();

		timer += Time::delta();

		if (timer >= 1.0f)
		{
			timer -= 1.0f;
			fps = frameCount;
			frameCount = 0;
			Console::Log("[LOG] FPS: %s\n", std::to_string(fps).c_str());
		}
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
