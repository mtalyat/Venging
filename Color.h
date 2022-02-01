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

	/// <summary>
	/// Gets the red value.
	/// </summary>
	/// <returns></returns>
	int r();
	/// <summary>
	/// Gets the red value between 0.0f and 1.0f.
	/// </summary>
	/// <returns></returns>
	float rf();

	/// <summary>
	/// Gets the green value.
	/// </summary>
	/// <returns></returns>
	int g();
	/// <summary>
	/// Gets the green value between 0.0f and 1.0f.
	/// </summary>
	/// <returns></returns>
	float gf();

	/// <summary>
	/// Gets the blue value.
	/// </summary>
	/// <returns></returns>
	int b();
	/// <summary>
	/// Gets the blue value between 0.0f and 1.0f.
	/// </summary>
	/// <returns></returns>
	float bf();

	/// <summary>
	/// Gets the alpha value.
	/// </summary>
	/// <returns></returns>
	int a();
	/// <summary>
	/// Gets the alpha value between 0.0f and 1.0f.
	/// </summary>
	/// <returns></returns>
	float af();

	/// <summary>
	/// Gets the raw stored data value.
	/// </summary>
	/// <returns></returns>
	int rawData() const;

	std::string toString() override;

	//the following are all shorthand for their respective colors
	static Color white() { return Color(255, 255, 255); }
	static Color gray() { return Color(127, 127, 127); }
	static Color black() { return Color(0, 0, 0); }
private:
	unsigned int data;

	void set(int r, int g, int b, int a);
};

#endif