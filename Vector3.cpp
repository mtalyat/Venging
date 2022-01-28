#include "Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(glm::vec3 v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3::Vector3(float initX, float initY)
{
	x = initX;
	y = initY;
	z = 0.0f;
}

Vector3::Vector3(float initX, float initY, float initZ)
{
	x = initX;
	y = initY;
	z = initZ;
}

Vector3::Vector3(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

float Vector3::getMagnitude()
{
	return sqrt(getSqrMagnitude());
}

float Vector3::getSqrMagnitude()
{
	return std::pow(x, 2.0f) + std::pow(y, 2.0f) + std::pow(z, 2.0f);
}

Vector3& Vector3::operator=(Vector3 const& obj)
{
	x = obj.x;
	y = obj.y;
	z = obj.z;

	return *this;
}

Vector3 Vector3::operator+(Vector3 const& obj)
{
	return Vector3(x + obj.x, y + obj.y, z + obj.z);
}

Vector3 Vector3::operator-(Vector3 const& obj)
{
	return Vector3(x - obj.x, y - obj.y, z - obj.z);
}

Vector3 Vector3::operator*(Vector3 const& obj)
{
	return Vector3(x * obj.x, y * obj.y, z * obj.z);
}

Vector3 Vector3::operator/(Vector3 const& obj)
{
	return Vector3(x / obj.x, y / obj.y, z / obj.z);
}

Vector3 Vector3::operator*(float const& obj)
{
	return Vector3(x * obj, y * obj, z * obj);
}

Vector3 Vector3::operator/(float const& obj)
{
	return Vector3(x / obj, y / obj, z / obj);
}

/// <summary>
/// Shorthand for Vector3(0.0f, 1.0f, 0.0f).
/// </summary>
/// <returns></returns>
Vector3 Vector3::up()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

/// <summary>
/// Shorthand for Vector3(0.0f, -1.0f, 0.0f).
/// </summary>
/// <returns></returns>
Vector3 Vector3::down()
{
	return Vector3(0.0f, -1.0f, 0.0f);
}

/// <summary>
/// Shorthand for Vector3(-1.0f, 0.0f, 0.0f).
/// </summary>
/// <returns></returns>
Vector3 Vector3::left()
{
	return Vector3(-1.0f, 0.0f, 0.0f);
}

/// <summary>
/// Shorthand for Vector3(1.0f, 0.0f, 0.0f).
/// </summary>
/// <returns></returns>
Vector3 Vector3::right()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

/// <summary>
/// Shorthand for Vector3(0.0f, 0.0f, 1.0f).
/// </summary>
/// <returns></returns>
Vector3 Vector3::forward()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

/// <summary>
/// Shorthand for Vector3(0.0f, 0.0f, -1.0f).
/// </summary>
/// <returns></returns>
Vector3 Vector3::backward()
{
	return Vector3(0.0f, 0.0f, -1.0f);
}

/// <summary>
/// Shorthand for Vector3(0.0f, 0.0f, 0.0f).
/// </summary>
/// <returns></returns>
Vector3 Vector3::zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}

/// <summary>
/// Shorthand for Vector3(1.0f, 1.0f, 1.0f).
/// </summary>
/// <returns></returns>
Vector3 Vector3::one()
{
	return Vector3(1.0f, 1.0f, 1.0f);
}

std::string Vector3::toString()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}
