#include "Random.h"

bool Random::isInitialized = false;

void Random::seed(const long unsigned int seed)
{
	srand(seed);

	isInitialized = true;
}

int Random::range(const int min, const int max)
{
	if (!isInitialized)
	{
		seed(time(0));
	}

	if (min == max)
	{
		return 0;
	}
	else if (min > max)
	{
		Console::LogError("Given argument min is greater than given argument max!");
		return 0;
	}

	return (rand() % (max - min)) + min;
}
