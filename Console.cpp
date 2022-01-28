#include "Console.h"

/// <summary>
/// Logs a message to the console.
/// </summary>
/// <param name="message"></param>
void Console::Log(const std::string message)
{
	std::cout << "[LOG] " << message << std::endl;
}

void Console::Log(Object obj)
{
	Log(obj.toString());
}

/// <summary>
/// Logs a warning to the console.
/// </summary>
/// <param name="message"></param>
void Console::LogWarning(const std::string message)
{
	std::cout << "[WRN] " << message << std::endl;
}

void Console::LogWarning(Object obj)
{
	LogWarning(obj.toString());
}

/// <summary>
/// Logs a warning to the console.
/// </summary>
/// <param name="message"></param>
void Console::LogError(const std::string message)
{
	std::cout << "[ERR] " << message << std::endl;
}

void Console::LogError(Object obj)
{
	LogError(obj.toString());
}
