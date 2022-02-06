#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "Component.h"
#include "System.h"
#include "Shader.h"
#include "CameraComponent.h"
#include "Window.h"
#include "Vector3.h"
#include "TransformComponent.h"

/// <summary>
/// Provides data for a Camera within a Scene. Cameras provide perspective for rendering to the screen. The mainCamera is the one that will be rendered to the screen each frame.
/// </summary>
class CameraComponent
	: public Component
{
public:
	CameraComponent();

	/// <summary>
	/// Rotates the view matrix to render all the objects in 3D to the 2D screen, from Camera::mainCamera's perspective.
	/// </summary>
	/// <param name="FOVdeg"></param>
	/// <param name="nearPlane"></param>
	/// <param name="farPlane"></param>
	/// <param name="shader"></param>
	/// <param name="uniform"></param>
	/// <param name="window"></param>
	void matrix(float FOVdeg, float nearPlane, float farPlane, Shader* shader, const char* uniform, Window* window);

	/// <summary>
	/// Sets this Camera as the main Camera.
	/// </summary>
	void setAsMain();

	/// <summary>
	/// Sets the given Camera as the main Camera.
	/// </summary>
	/// <param name="cam"></param>
	static void setMain(CameraComponent* cam);

	/// <summary>
	/// Gets the main Camera.
	/// </summary>
	/// <returns></returns>
	static CameraComponent* main();
private:
	static CameraComponent* mainCamera;
};

#endif