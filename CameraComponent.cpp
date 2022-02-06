#include "CameraComponent.h"

CameraComponent* CameraComponent::mainCamera = nullptr;

CameraComponent::CameraComponent() : Component()
{
	//if no main camera, set to this one
	if (mainCamera == nullptr)
	{
		mainCamera = this;
	}
}

void CameraComponent::matrix(float FOVdeg, float nearPlane, float farPlane, Shader* shader, const char* uniform, Window* window)
{
	//get the position from the main camera
	glm::vec3 vPos = transform()->getPosition();
	glm::vec3 pos(vPos.x, vPos.y, vPos.z);

	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(pos, pos + transform()->getRotation(), TransformComponent::up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)window->getWidth() / window->getHeight(), nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	//glUniformMatrix4fv(glGetUniformLocation(shader->ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
	shader->setMatrix4(projection * view, "camMatrix");
}

void CameraComponent::setAsMain()
{
	setMain(this);
}

void CameraComponent::setMain(CameraComponent* cam)
{
	mainCamera = cam;
}

CameraComponent* CameraComponent::main()
{
	return mainCamera;
}
