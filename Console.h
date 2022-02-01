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
	static void Log(const char* message);
	/// <summary>
	/// Prints an Object to the Console.
	/// </summary>
	/// <param name="obj"></param>
	static void Log(Object* obj);

	static void Log(const char* message, const char* s0);
	static void Log(const char* message, const char* s0, const char* s1);
	static void Log(const char* message, const char* s0, const char* s1, const char* s2);
	static void Log(const char* message, const char* s0, const char* s1, const char* s2, const char* s3);

	/// <summary>
	/// Prints a warning string to the Console.
	/// </summary>
	/// <param name="message"></param>
	static void LogWarning(const char* message);
	/// <summary>
	/// Prints a warning Object to the Console.
	/// </summary>
	/// <param name="obj"></param>
	static void LogWarning(Object* obj);

	/// <summary>
	/// Prints a error string to the Console.
	/// </summary>
	/// <param name="message"></param>
	static void LogError(const char* message);
	/// <summary>
	/// Prints an error Object to the Console.
	/// </summary>
	/// <param name="obj"></param>
	static void LogError(Object* obj);
};

#endif
