#include "Console.h"

/// <summary>
/// Logs a message to the console.
/// </summary>
/// <param name="message"></param>
void Console::Log(const char* message)
{
	std::cout << "[LOG] " << message << std::endl;
}

void Console::Log(Object* obj)
{
	Log(obj->toString().c_str());
}

void Console::Log(const char* message, const char* s0)
{
	printf(message, s0);
}

void Console::Log(const char* message, const char* s0, const char* s1)
{
	printf(message, s0, s1);
}

void Console::Log(const char* message, const char* s0, const char* s1, const char* s2)
{
	printf(message, s0, s1, s2);
}

void Console::Log(const char* message, const char* s0, const char* s1, const char* s2, const char* s3)
{
	printf(message, s0, s1, s2, s3);
}

/// <summary>
/// Logs a warning to the console.
/// </summary>
/// <param name="message"></param>
void Console::LogWarning(const char* message)
{
	std::cout << "[WRN] " << message << std::endl;
}

void Console::LogWarning(Object* obj)
{
	LogWarning(obj->toString().c_str());
}

/// <summary>
/// Logs a warning to the console.
/// </summary>
/// <param name="message"></param>
void Console::LogError(const char* message)
{
	std::cout << "[ERR] " << message << std::endl;
}

void Console::LogError(Object* obj)
{
	LogError(obj->toString().c_str());
}
