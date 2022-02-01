#include "Time.h"

float Time::deltaTime = 0.0f;
float Time::timeSinceStartup = 0.0f;

float Time::delta()
{
    return deltaTime;
}

float Time::time()
{
    return timeSinceStartup;
}
