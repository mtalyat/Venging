#ifndef COLOR_H
#define COLOR_H

#include "Object.h"

/// <summary>
/// Represents a Color in red, green, blue and alpha colors as floats from 0.0 to 1.0 (inclusive).
/// </summary>
struct Color
	: public Object
{
public:
	float r;
	float g;
	float b;
	float a;

	/// <summary>
	/// Creates a new Color, defaulted to black.
	/// </summary>
	Color();

	/// <summary>
	/// Creates a new Color using the given RGB colors. Alpha is defaulted to 1.0f.
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	Color(float r, float g, float b);

	/// <summary>
	/// Creates a new Color using the given RGBA colors.
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <param name="a"></param>
	Color(float r, float g, float b, float a);

	/// <summary>
	/// Shorthand to create a Color that represents the color white.
	/// </summary>
	/// <returns></returns>
	static Color white() { return Color(1.0f, 1.0f, 1.0f); }

	/// <summary>
	/// Shorthand to create a Color that represents the color black.
	/// </summary>
	/// <returns></returns>
	static Color black() { return Color(0.0f, 0.0f, 0.0f); }
};

#endif