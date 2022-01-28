#include "Scene.h"

Scene::Scene()
{
	isInitialized = false;
	isStarted = false;

	shaderProgram = nullptr;
	vao = nullptr;
	vbo = nullptr;
	ebo = nullptr;

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
	Console::Log("Attempting to initialize scene");

	if (isInitialized)
	{
		Console::Log("Failed to initialize scene.");
		return;
	}

	isInitialized = true;

	//init all systems

	int i = 0;
	for (; i < systems.length(); i++)
	{
		systems[i]->init();
	}

	//	triangle stuff
	GLfloat vertices[] =
	{
		//	coordinates				colors
		-0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	//bottom left forward
		-0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	//bottom left backward
		0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	//bottom right backward
		0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	//bottom right forward
		0.0f, 0.8f, 0.0f,		0.92f, 0.86f, 0.76f,	//top
	};

	//triangles' indices for the vertices
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 1,
		1, 4, 2,
		2, 4, 3,
		3, 4, 0,
	};

	//finish initializing the scene
	shaderProgram = new Shader("default.vert", "default.frag");

	vao = new VAO();
	vao->bind();

	vbo = new VBO(vertices, sizeof(vertices));
	ebo = new EBO(indices, sizeof(indices));

	//link vertices to vec3 in shader
	vao->linkAttribute(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	//link colors to vec3 in shader
	vao->linkAttribute(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//all done with VAO, VBO and EBO
	vao->unbind();
	vbo->unbind();
	ebo->unbind();

	Console::Log("Scene initialized");
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
	//activate shader first
	shaderProgram->activate();

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

	vao->close();
	vbo->close();
	ebo->close();
	shaderProgram->close();

	delete(vao);
	delete(vbo);
	delete(ebo);
	delete(shaderProgram);
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
	Camera::main()->inputs(window);
	Camera::main()->matrix(45.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix", window);

	//rebind vao
	vao->bind();

	//pretending like we know the amount for now (18)
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	//swap buffers on screen so it gets updated
	glfwSwapBuffers(window->glfwWindow());

	//do window events
	glfwPollEvents();
}