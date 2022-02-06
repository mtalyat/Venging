#ifndef CAMERACONTROLLERCOMPONENT_H
#define CAMERACONTROLLERCOMPONENT_H

#include <glm/glm.hpp>
#include "Component.h"

class CameraControllerComponent :
    public Component
{
public:
	friend class CameraControllerSystem;
private:
	bool firstClick = false;

	float speed = 0.01f;
	float sensitivity = 100.0f;
};

#endif
