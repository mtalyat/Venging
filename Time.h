#ifndef TIME_H
#define TIME_H

#include "Object.h"

class Time
	: public Object
{
	//so Engine can set the private static variables
	friend class Engine;

public:
	/// <summary>
	/// Gets the amount of time that passed over the previous frame.
	/// </summary>
	/// <returns></returns>
	static float delta();

	/// <summary>
	/// Gets the amount of time that has passed since the Engine has started running.
	/// </summary>
	/// <returns></returns>
	static float time();
private:
	//these variables are set by Engine when running
	static float deltaTime;
	static float timeSinceStartup;
};

#endif
