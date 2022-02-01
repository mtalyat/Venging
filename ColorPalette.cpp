#include "ColorPalette.h"

ColorPalette::ColorPalette()
{
	colors = new Color[COLOR_COUNT];
}

ColorPalette::ColorPalette(const char* filename)
{
	//amount of numbers that should be in the file = 256 (total colors in a palette) * 3 (for each r g b value)
	const int numberAmount = COLOR_COUNT * 3;

	int numbers[numberAmount];

	readNumbersFromFile(filename, numbers, numberAmount);

	colors = new Color[COLOR_COUNT];

	//now convert into colors
	int i = 0;
	int j;
	for (; i < COLOR_COUNT; i++)
	{
		j = i * 3;
		colors[i] = Color(numbers[j], numbers[j + 1], numbers[j + 2]);
	}
}

ColorPalette::~ColorPalette()
{
	delete(colors);
}

void ColorPalette::set(const int index, Color c)
{
}

Color ColorPalette::get(const int index)
{
	return Color();
}
