#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>
#include <glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <cmath>
#include "Object.h"

/// <summary>
/// A 3D vector.
/// </summary>
struct Vector3 :
	public Object
{
public:
	float x;
	float y;
	float z;

	/// <summary>
	/// Creates a new Vector3 initialzed at the origin (0, 0, 0).
	/// </summary>
	Vector3();
	/// <summary>
	/// Converts a glm::vec3 to a Vector3.
	/// </summary>
	/// <param name="v"></param>
	Vector3(glm::vec3 v);
	/// <summary>
	/// Creates a new Vector3 initialized at (initX, initY, 0).
	/// </summary>
	/// <param name="initX">The initial x value.</param>
	/// <param name="initY">The initial y value.</param>
	Vector3(float initX, float initY);
	/// <summary>
	/// Creates a new Vector3 initialized at (initX, initY, initZ).
	/// </summary>
	/// <param name="initX">The initial x value.</param>
	/// <param name="initY">The initial y value.</param>
	/// <param name="initZ">The initial z value.</param>
	Vector3(float initX, float initY, float initZ);

	Vector3(int initX, int initY);
	Vector3(int initX, int initY, int initZ);

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="v"></param>
	Vector3(const Vector3& v);


	/// <summary>
	/// Gets the magnitude (length) of the Vector3.
	/// </summary>
	/// <returns></returns>
	float getMagnitude();
	/// <summary>
	/// Gets the magnitude (length) of the Vector3, squared.
	/// </summary>
	/// <returns></returns>
	float getSqrMagnitude();

	/// <summary>
	/// Assignment operator.
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	Vector3& operator = (Vector3 const& obj);
	/// <summary>
	/// Addition operator. Adds two Vector3s together.
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	Vector3 operator + (Vector3 const& obj);
	/// <summary>
	/// subtraction operator. Subtracts the given Vector3 from this Vector3.
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	Vector3 operator - (Vector3 const& obj);
	/// <summary>
	/// Multiplication operator. Multiplies two Vector3s together.
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	Vector3 operator * (Vector3 const& obj);
	/// <summary>
	/// Division operator. Divides the given Vector3 into this Vector3.
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	Vector3 operator / (Vector3 const& obj);
	/// <summary>
	/// Multiplication operator. Multiplies this Vector3 by the given float.
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	Vector3 operator * (float const& obj);
	/// <summary>
	/// Division operator. Dividies this Vector3 by the given float.
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	Vector3 operator / (float const& obj);

	/// <summary>
	/// Shorthand to create a Vector3 pointing up.
	/// </summary>
	/// <returns>Vector3(0, 1, 0)</returns>
	static Vector3 up();
	/// <summary>
	/// Shorthand to create a Vector3 pointing down.
	/// </summary>
	/// <returns>Vector3(0, -1, 0)</returns>
	static Vector3 down();
	/// <summary>
	/// Shorthand to create a Vector3 pointing left.
	/// </summary>
	/// <returns>Vector3(-1, 0, 0)</returns>
	static Vector3 left();
	/// <summary>
	/// Shorthand to create a Vector3 pointing right.
	/// </summary>
	/// <returns>Vector3(1, 0, 0)</returns>
	static Vector3 right();
	/// <summary>
	/// Shorthand to create a Vector3 pointing forward.
	/// </summary>
	/// <returns>Vector3(0, 0, 1)</returns>
	static Vector3 forward();
	/// <summary>
	/// Shorthand to create a Vector3 pointing backward.
	/// </summary>
	/// <returns>Vector3(0, 0, -1)</returns>
	static Vector3 backward();

	/// <summary>
	/// Shorthand to create a Vector3 composing of all 1s.
	/// </summary>
	/// <returns>Vector3(1, 1, 1)</returns>
	static Vector3 zero();
	/// <summary>
	/// Shorthand to create a Vector3 composing of all 0s.
	/// </summary>
	/// <returns>Vector3(0, 0, 0)</returns>
	static Vector3 one();

	std::string toString() override;

	glm::vec3 toVec3();
};

#endif
