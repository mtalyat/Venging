#include "Window.h"

bool Window::isInitialized = false;
unsigned int Window::openWindowCount = 0;

Window::Window(const char* title)
{
	backgroundColor = Color::white();

	if (!isInitialized)
	{
		initialize();
	}

	openWindowCount++;

	this->width = 640;
	this->height = 480;

	initializeWindow(title, true);
}

Window::Window(int width, int height, const char* title)
{
	backgroundColor = Color::white();

	if (!isInitialized)
	{
		initialize();
	}

	openWindowCount++;

	this->width = width;
	this->height = height;

	initializeWindow(title, false);
}

Window::~Window()
{
	openWindowCount--;

	if (openWindowCount == 0)
	{
		//if all windows have been closed, close glfw
		glfwDestroyWindow(windowPtr);
		glfwTerminate();
	}
}

void Window::setBackgroundColor(Color color)
{
	backgroundColor = color;
}

void Window::clear()
{
	glClearColor(backgroundColor.rf(), backgroundColor.gf(), backgroundColor.bf(), backgroundColor.af());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow* Window::glfwWindow()
{
	return windowPtr;
}

int Window::getWidth()
{
	glfwGetWindowSize(windowPtr, &width, &height);

	return width;
}

int Window::getHeight()
{
	glfwGetWindowSize(windowPtr, &width, &height);

	return height;
}

void Window::initialize()
{
	isInitialized = true;

	//initialize glfw
	glfwInit();

	//tell GLFW what version of OpenGL we are using
	//downloaded version 3 (3.3) for this
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//tell it what profile/set of commands we are using
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//load glad
	//gladLoadGL();
}

void Window::initializeWindow(const char* title, bool isFullScreen)
{
	//create the glfw window
	if (isFullScreen)
	{
		windowPtr = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		windowPtr = glfwCreateWindow(width, height, title, NULL, NULL);
	}

	if (!checkIfWindowCreationSuccessful())
	{
		return;
	}

	//make this the window in focus
	glfwMakeContextCurrent(windowPtr);

	//load the GL
	gladLoadGL();

	//keyboard input
	glfwSetKeyCallback(windowPtr, Input::keyCallback);

	//create a port to be able to draw on in the window
	glViewport(0, 0, width, height);

	//create crop area too
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 0, width, height);

	//resize event
	glfwSetWindowSizeCallback(windowPtr, [](GLFWwindow* win, int w, int h)
		{
			glViewport(0, 0, w, h);
			glScissor(0, 0, w, h);//only if scissor test enabled
		});
}

bool Window::checkIfWindowCreationSuccessful()
{
	if (windowPtr == NULL)
	{
		Console::LogError("Failed to create GLFW Window.");
		
		return false;
	}

	return true;
}