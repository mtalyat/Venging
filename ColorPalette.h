#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include "Object.h"
#include "Color.h"
#include "Helper.h"

#define COLOR_COUNT 256

class ColorPalette :
	public Object
{
public:
	/// <summary>
	/// Creates an empty color palette.
	/// </summary>
	ColorPalette();
	ColorPalette(const char* filename);

	~ColorPalette();

	void set(const int index, Color c);
	Color get(const int index);
private:
	//initialize to default palette
	Color* colors;
};

#endif
