#include "Input.h"

ActionMap* Input::currentMap = nullptr;
std::map<const char*, ActionMap> Input::maps = std::map<const char*, ActionMap>();
std::map<int, int> Input::keyStates = std::map<int, int>();

void Input::setCurrentActionMap(const char* name)
{
	currentMap = &maps[name];
}

ActionMap* Input::createActionMap(const char* name)
{
	maps[name] = ActionMap();

	if (currentMap == nullptr)
	{
		currentMap = &maps[name];
	}

	return &maps[name];
}

void Input::onKeyDown(const int key, std::function<void()> func)
{
	if (currentMap == nullptr)
	{
		Console::LogError("Attempted to use onKeyDown before adding an ActionMap to Input.");
		return;
	}

	currentMap->onKeyDown(key, func);
}

void Input::onKeyPress(const int key, std::function<void()> func)
{
	if (currentMap == nullptr)
	{
		Console::LogError("Attempted to use onKeyPress before adding an ActionMap to Input.");
		return;
	}

	currentMap->onKeyPress(key, func);
}

void Input::onKeyUp(const int key, std::function<void()> func)
{
	if (currentMap == nullptr)
	{
		Console::LogError("Attempted to use onKeyUp before adding an ActionMap to Input.");
		return;
	}

	currentMap->onKeyUp(key, func);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (currentMap == nullptr)
	{
		Console::LogError("No ActionMap has been added to class Input.");
		return;
	}

	if (action == GLFW_PRESS)//key down
	{
		keyStates[key] = INPUT_DOWN;
	}
	else if (action == GLFW_RELEASE)//key up
	{
		keyStates[key] = INPUT_UP;
	}
}

void Input::cursorCallback(GLFWwindow* window, double xPos, double yPos)
{

}

void Input::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{

}

void Input::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{

}

void Input::doInputEvents()
{
	if (currentMap == nullptr)
	{
		return;
	}

	for (const auto& kv : keyStates)
	{
		switch (kv.second)
		{
		case INPUT_PRESSED://when pressed, run event
			currentMap->logKeyPress(kv.first);
			break;
		case INPUT_DOWN://when down, run event them move to pressed
			currentMap->logKeyDown(kv.first);
			keyStates[kv.first] = INPUT_PRESSED;
			break;
		case INPUT_UP://when up, run event then move to released
			currentMap->logKeyUp(kv.first);
			keyStates[kv.first] = INPUT_RELEASED;
			break;
			
			//if INPUT_RELEASED, do nothing
		}
	}
}
