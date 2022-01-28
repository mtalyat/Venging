#include "Camera.h"

Camera* Camera::mainCamera = nullptr;

Camera::Camera() : Component()
{
	//if no main camera, set to this one
	if (mainCamera == nullptr)
	{
		mainCamera = this;
	}
}

void Camera::matrix(float FOVdeg, float nearPlane, float farPlane, Shader* shader, const char* uniform, Window* window)
{
	//get the position from the main camera
	Vector3 vPos = transform()->getPosition();
	glm::vec3 pos(vPos.x, vPos.y, vPos.z);

	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(pos, pos + orientation, up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)window->getWidth() / window->getHeight(), nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(Window* window)
{
	// Handles key inputs
	if (glfwGetKey(window->glfwWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		transform()->movePosition(speed * orientation);
	}
	if (glfwGetKey(window->glfwWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		transform()->movePosition(speed * -glm::normalize(glm::cross(orientation, up)));
	}
	if (glfwGetKey(window->glfwWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		transform()->movePosition(speed * -orientation);
	}
	if (glfwGetKey(window->glfwWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		transform()->movePosition(speed * glm::normalize(glm::cross(orientation, up)));
	}
	if (glfwGetKey(window->glfwWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		transform()->movePosition(speed * up);
	}
	if (glfwGetKey(window->glfwWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		transform()->movePosition(speed * -up);
	}
	if (glfwGetKey(window->glfwWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window->glfwWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	// Handles mouse inputs
	if (glfwGetMouseButton(window->glfwWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window->glfwWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window->glfwWindow(), (window->getWidth() / 2), (window->getHeight() / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window->glfwWindow(), &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (window->getHeight() / 2)) / window->getHeight();
		float rotY = sensitivity * (float)(mouseX - (window->getWidth() / 2)) / window->getWidth();

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		orientation = glm::rotate(orientation, glm::radians(-rotY), up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window->glfwWindow(), (window->getWidth() / 2), (window->getHeight() / 2));
	}
	else if (glfwGetMouseButton(window->glfwWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window->glfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}

void Camera::setAsMain()
{
	setMain(this);
}

void Camera::setMain(Camera* cam)
{
	mainCamera = cam;
}

Camera* Camera::main()
{
	return mainCamera;
}
