#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <stdlib.h>
#include <cstdbool>
#include <algorithm>
#include "Console.h"

class Random
{
public:
	static void seed(long unsigned int seed);

	/// <summary>
	/// Gets a random value between min (inclusive) and max (exclusive).
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	static int range(const int min, const int max);
private:
	static bool isInitialized;
};

#endif
