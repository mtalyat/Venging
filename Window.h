#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <cstdbool>
#include <glad/glad.h>
#include "Console.h"
#include "Color.h"
#include "Object.h"
#include "Input.h"

/// <summary>
/// A wrapper class for the GLFWwindow class.
/// </summary>
class Window
	: public Object
{
public:
	/// <summary>
	/// Creates a full screen Window.
	/// </summary>
	Window(const char* title);

	/// <summary>
	/// Creates a Window of the given width and height.
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="title"></param>
	Window(int width, int height, const char* title);

	~Window();

	/// <summary>
	/// Sets the background/clear color for this Window.
	/// </summary>
	/// <param name="color"></param>
	void setBackgroundColor(Color color);
	/// <summary>
	/// Clears this Window using the background color.
	/// </summary>
	void clear();

	/// <summary>
	/// Gets the GLFWwindow.
	/// </summary>
	/// <returns></returns>
	GLFWwindow* glfwWindow();

	/// <summary>
	/// Gets the width of the Window.
	/// </summary>
	/// <returns></returns>
	int getWidth();

	/// <summary>
	/// Gets the height of the Window.
	/// </summary>
	/// <returns></returns>
	int getHeight();

	static Window* active();
private:
	int width;
	int height;
	Color backgroundColor;

	GLFWwindow* windowPtr;

	/// <summary>
	/// Initializes a GLFWwindow based on the given arguments.
	/// </summary>
	/// <param name="title"></param>
	/// <param name="isFullScreen"></param>
	void initializeWindow(const char* title, bool isFullScreen);

	/// <summary>
	/// Checks if the windowPtr is null and acts accordingly.
	/// </summary>
	/// <returns></returns>
	bool checkIfWindowCreationSuccessful();

	static void initialize();
	static bool isInitialized;
	static unsigned int openWindowCount;

	static Window* activeWindow;
};

#endif