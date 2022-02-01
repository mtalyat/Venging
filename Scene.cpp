#include "Scene.h"

Scene::Scene()
{
	isInitialized = false;
	isStarted = false;

	systems = List<System*>();
	entities = List<Entity*>();
}

Scene::~Scene()
{
	stop();
}

void Scene::instantiate(Entity* e)
{
	instantiate(e, Vector3());
}

void Scene::instantiate(Entity* e, Vector3 position)
{
	instantiate(e, position, nullptr);
}

void Scene::instantiate(Entity* e, Vector3 position, Transform* parent)
{
	e->transform()->setParent(parent);

	e->transform()->setPosition(position);

	entities.add(e);
}

void Scene::addSystem(System* system)
{
	systems.add(system);
}

void Scene::init()
{
	Console::Log("Attempting to initialize Scene.");

	if (isInitialized)
	{
		Console::LogError("Failed to initialize Scene.");
		return;
	}

	isInitialized = true;

	//init all systems

	int i = 0;
	for (; i < systems.length(); i++)
	{
		systems[i]->init();

		//if system is a renderingsystem, save it
		if (typeid(*systems[i]) == typeid(RenderingSystem))
		{
			renderSystem = (RenderingSystem*)systems[i];
		}
	}

	Console::Log("Scene initialized.");
}

void Scene::start()
{
	if (isStarted)
	{
		return;
	}

	isStarted = true;

	//start all systems
	int i = 0;
	for (; i < systems.length(); i++)
	{
		systems[i]->start();
	}
}

void Scene::update()
{
	//update all systems
	int i = 0;
	for (; i < systems.length(); i++)
	{
		systems[i]->update();
	}

	//camera input and camera matrix

}

void Scene::fixedUpdate()
{
	//fixed update all systems
	int i = 0;
	for (; i < systems.length(); i++)
	{
		systems[i]->fixedUpdate();
	}
}

void Scene::stop()
{
	if (!isInitialized)
	{
		return;
	}

	isInitialized = false;
	isStarted = false;
}

void Scene::render(Window* window)
{
	//camera events
	if (Camera::main() == nullptr)
	{
		//cannot render anything if no camera
		Console::LogError("There is no main Camera assigned in the Scene!");
		return;
	}

	if (renderSystem == nullptr)
	{
		//will not render anything if no rendering system
		Console::LogWarning("There is no RenderingSystem in the Scene. Nothing will be drawn.");
		return;
	}

	renderSystem->render(window);

	//swap buffers on screen so it gets updated
	glfwSwapBuffers(window->glfwWindow());

	//do window events
	glfwPollEvents();
}