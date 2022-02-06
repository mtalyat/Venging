#ifndef CAMERACONTROLLERSYSTEM_H
#define CAMERACONTROLLERSYSTEM_H

#include <functional>
#include <cstdbool>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "System.h"
#include "Input.h"
#include "TransformComponent.h"
#include "List.h"
#include "CameraControllerComponent.h"
#include "Window.h"

class CameraControllerSystem :
    public System
{
public:
    CameraControllerSystem();

    void initEntity(const int index) override;
    void updateEntity(const int index) override;

    void addEntity(Entity* entity) override;
    bool removeEntity(Entity* entity) override;
private:
    List<CameraControllerComponent*> camControllers;
};

#endif