#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <iostream>
#include "Object.h"

/// <summary>
/// Responsible for logging to the console.
/// </summary>
class Console
{
public:
	/// <summary>
	/// Prints a string to the Console.
	/// </summary>
	/// <param name="message"></param>
	static void Log(const std::string message);
	/// <summary>
	/// Prints an Object to the Console.
	/// </summary>
	/// <param name="obj"></param>
	static void Log(Object obj);

	/// <summary>
	/// Prints a warning string to the Console.
	/// </summary>
	/// <param name="message"></param>
	static void LogWarning(const std::string message);
	/// <summary>
	/// Prints a warning Object to the Console.
	/// </summary>
	/// <param name="obj"></param>
	static void LogWarning(Object obj);

	/// <summary>
	/// Prints a error string to the Console.
	/// </summary>
	/// <param name="message"></param>
	static void LogError(const std::string message);
	/// <summary>
	/// Prints an error Object to the Console.
	/// </summary>
	/// <param name="obj"></param>
	static void LogError(Object obj);
};

#endif
