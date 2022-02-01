#ifndef CAMERA_H
#define CAMERA_H

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
#include "Camera.h"
#include "Window.h"
#include "Vector3.h"
#include "Transform.h"

/// <summary>
/// Provides data for a Camera within a Scene. Cameras provide perspective for rendering to the screen. The mainCamera is the one that will be rendered to the screen each frame.
/// </summary>
class Camera
	: public Component
{
public:
	Camera();

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
	/// TEMP: Processes inputs from the Camera.
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="window"></param>
	void inputs(Window* window, Shader* shaderProgram);

	/// <summary>
	/// Sets this Camera as the main Camera.
	/// </summary>
	void setAsMain();

	/// <summary>
	/// Sets the given Camera as the main Camera.
	/// </summary>
	/// <param name="cam"></param>
	static void setMain(Camera* cam);

	/// <summary>
	/// Gets the main Camera.
	/// </summary>
	/// <returns></returns>
	static Camera* main();
private:
	static Camera* mainCamera;

	bool firstClick = false;

	float speed = 0.01f;
	float sensitivity = 100.0f;

	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif