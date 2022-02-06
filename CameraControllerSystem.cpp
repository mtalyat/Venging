#include "CameraControllerSystem.h"

CameraControllerSystem::CameraControllerSystem()
{

}

void CameraControllerSystem::initEntity(const int index)
{
	Entity* e = entities[index];
	CameraControllerComponent* ccc = camControllers[index];
	TransformComponent* t = e->transform();

	//set rotation to -z
	t->setRotation(glm::vec3(0.0f, 0.0f, -1.0f));

	Input::onKeyPress(GLFW_KEY_W, std::function<void()>([e, ccc, t]() {	//W
		e->transform()->movePosition(ccc->speed * t->getRotation());
		}));

	Input::onKeyPress(GLFW_KEY_A, std::function<void()>([e, ccc, t]() {	//A
		e->transform()->movePosition(ccc->speed * -glm::normalize(glm::cross(t->getRotation(), TransformComponent::up)));
		}));

	Input::onKeyPress(GLFW_KEY_S, std::function<void()>([e, ccc, t]() {	//S
		e->transform()->movePosition(ccc->speed * -t->getRotation());
		}));

	Input::onKeyPress(GLFW_KEY_D, std::function<void()>([e, ccc, t]() {	//D
		e->transform()->movePosition(ccc->speed * glm::normalize(glm::cross(t->getRotation(), TransformComponent::up)));
		}));

	Input::onKeyPress(GLFW_KEY_SPACE, std::function<void()>([e, ccc]() {	//space
		e->transform()->movePosition(ccc->speed * TransformComponent::up);
		}));

	Input::onKeyPress(GLFW_KEY_LEFT_CONTROL, std::function<void()>([e, ccc]() {	//L Ctrl
		e->transform()->movePosition(ccc->speed * -TransformComponent::up);
		}));

	Input::onKeyDown(GLFW_KEY_LEFT_SHIFT, std::function<void()>([ccc]() {	//L Shift down
		ccc->speed = 0.4f;
		}));

	Input::onKeyUp(GLFW_KEY_LEFT_SHIFT, std::function<void()>([ccc]() {	//L Shift up
		ccc->speed = 0.1f;
		}));
}

void CameraControllerSystem::updateEntity(const int index)
{
	Window* window = Window::active();

	CameraControllerComponent* ccc = camControllers[index];

	TransformComponent* t = entities[index]->transform();
	glm::vec3 orientation = t->getRotation();

	// Handles mouse inputs
	if (glfwGetMouseButton(window->glfwWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window->glfwWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (ccc->firstClick)
		{
			glfwSetCursorPos(window->glfwWindow(), (window->getWidth() / 2), (window->getHeight() / 2));
			ccc->firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window->glfwWindow(), &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = ccc->sensitivity * (float)(mouseY - (window->getHeight() / 2)) / window->getHeight();
		float rotY = ccc->sensitivity * (float)(mouseX - (window->getWidth() / 2)) / window->getWidth();

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, TransformComponent::up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, TransformComponent::up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		orientation = glm::rotate(orientation, glm::radians(-rotY), TransformComponent::up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window->glfwWindow(), (window->getWidth() / 2), (window->getHeight() / 2));

		//finally, update actual rotation
		t->setRotation(orientation);

		
	}
	else if (glfwGetMouseButton(window->glfwWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window->glfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		ccc->firstClick = true;
	}
}

void CameraControllerSystem::addEntity(Entity* entity)
{
	CameraControllerComponent* ccc = entity->getComponent<CameraControllerComponent>();

	if (ccc == NULL)
	{
		Console::LogWarning("The given entity did not have an attached Camera Controller Component.");
		return;
	}

	System::addEntity(entity);
	camControllers.add(ccc);
}

bool CameraControllerSystem::removeEntity(Entity* entity)
{
	if (!System::removeEntity(entity))
	{
		//entity was not in this system
		return false;
	}

	camControllers.remove(entity->getComponent<CameraControllerComponent>());
}