#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include "Component.h"
#include "List.h"

class Entity;

/// <summary>
/// Transforms represent where an Entity is spacially represented in the Scene, in 3D space.
/// </summary>
class Transform :
	public Component
{
public:
	/// <summary>
	/// Creates a new Transform.
	/// </summary>
	Transform();
	/// <summary>
	/// Creates a new Transform that is on the given Entity.
	/// </summary>
	/// <param name="entityRef"></param>
	Transform(Entity& entityRef);
	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="other"></param>
	Transform(const Transform& other);

	/// <summary>
	/// Returns the Transform's position in world space.
	/// </summary>
	/// <returns></returns>
	glm::vec3 getPosition();
	/// <summary>
	/// Sets the Transform's position in world space.
	/// </summary>
	/// <param name="v"></param>
	void setPosition(glm::vec3 v);
	/// <summary>
	/// Moves the Transform in the given amount based on the current position.
	/// </summary>
	/// <param name="v"></param>
	void movePosition(glm::vec3 v);

	/// <summary>
	/// Gets the position of the Transform relative to the parent (or origin, if parent is null).
	/// </summary>
	/// <returns></returns>
	glm::vec3 getLocalPosition();
	/// <summary>
	/// Sets the position of the Transform relative to the parent (or origin, if parent is null).
	/// </summary>
	/// <returns></returns>
	void setLocalPosition(glm::vec3 v);

	/// <summary>
	/// Gets the global scale of this Transform.
	/// </summary>
	/// <returns></returns>
	glm::vec3 getScale();
	/// <summary>
	/// Sets the global scale of this Transform.
	/// </summary>
	/// <param name="v"></param>
	void setScale(glm::vec3 v);

	/// <summary>
	/// Gets the local scale of this Transform.
	/// </summary>
	/// <returns></returns>
	glm::vec3 getLocalScale();
	/// <summary>
	/// Sets the local scale of this Transform.
	/// </summary>
	/// <param name="v"></param>
	void setLocalScale(glm::vec3 v);

	/// <summary>
	/// Gets the parent of this Transform.
	/// </summary>
	/// <returns></returns>
	Transform* getParent();
	/// <summary>
	/// Sets the parent of this Transform.
	/// </summary>
	/// <param name="transform"></param>
	void setParent(Transform* transform);

	/// <summary>
	/// Gets the child Transform at the given index.
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	Transform* getChild(int index);
private:
	glm::vec3 localPosition;
	glm::vec3 localScale;

	Transform* parent;
	List<Transform*> children;

	/// <summary>
	/// Initializes this Transform be located at the origin with no parent.
	/// </summary>
	void init();

	/// <summary>
	/// Adds a child to this Transform.
	/// </summary>
	/// <param name="child"></param>
	void addChild(Transform* child);
	/// <summary>
	/// Removes a child from this Transform.
	/// </summary>
	/// <param name="child"></param>
	/// <returns></returns>
	bool removeChild(Transform* child);
};

#endif