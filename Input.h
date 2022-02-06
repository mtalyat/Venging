#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <map>
#include "Object.h"
#include "ActionMap.h"
#include "Console.h"

#define INPUT_RELEASED 0
#define INPUT_DOWN 1
#define INPUT_PRESSED 2
#define INPUT_UP 3

class Input :
    public Object
{
public:
    /// <summary>
    /// Sets the current ActionMap based on the given name.
    /// </summary>
    /// <param name="name"></param>
    static void setCurrentActionMap(const char* name);

    /// <summary>
    /// Creates a new ActionMap for the Input class. 
    /// If no ActionMap has been created yet, the first ActionMap created will be
    /// assigned to the current ActionMap.
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    static ActionMap* createActionMap(const char* name);

    /// <summary>
    /// Adds an event to when the given key is first pressed.
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    static void onKeyDown(const int key, std::function<void()> func);

    /// <summary>
    /// Adds an event to when the given key is held down.
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    static void onKeyPress(const int key, std::function<void()> func);

    /// <summary>
    /// Adds an event to when the given key is released.
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    static void onKeyUp(const int key, std::function<void()> func);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorCallback(GLFWwindow* window, double xPos, double yPos);
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    static void doInputEvents();
private:
    static ActionMap* currentMap;

    static std::map<const char*, ActionMap> maps;
    static std::map<int, int> keyStates;
};

#endif
