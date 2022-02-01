#ifndef COLOR_H
#define COLOR_H

#include "Object.h"
#include "Helper.h"

/// <summary>
/// Represents a Color in red, green, blue and alpha colors as floats from 0.0 to 1.0 (inclusive).
/// </summary>
struct Color
	: public Object
{
public:
	/// <summary>
	/// Creates a new Color, defaulted to black.
	/// </summary>
	Color();

	/// <summary>
	/// Creates a new Color using the given RGB colors. Alpha is defaulted to 255.
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	Color(int r, int g, int b);

	/// <summary>
	/// Creates a new Color using the given RGBA colors.
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <param name="a"></param>
	Color(int r, int g, int b, int a);

	//copy constructor
	Color(const Color& other);

	//assignment operator
	Color& operator = (const Color& obj);

	int r();
	float rf();

	int g();
	float gf();

	int b();
	float bf();

	int a();
	float af();

	std::string toString() override;

	//the following are all shorthand for their respective colors
	static Color white() { return Color(255, 255, 255); }
	static Color gray() { return Color(127, 127, 127); }
	static Color black() { return Color(0, 0, 0); }
private:
	int data;

	void set(int r, int g, int b, int a);
};

#endif