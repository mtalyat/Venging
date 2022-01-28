#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <typeinfo>

/// <summary>
/// The base class of all objects in Venging.
/// </summary>
class Object
{
public:
	/// <summary>
	/// Converts this Object to a string.
	/// </summary>
	/// <returns></returns>
	virtual std::string toString();
};

#endif
