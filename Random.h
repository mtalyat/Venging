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
	/// <summary>
	/// Initializes Random with the given seed. If this method is never called, the seed will be set to time(0) upon the first call of any other method.
	/// </summary>
	/// <param name="seed"></param>
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
