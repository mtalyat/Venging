#ifndef ACTIONMAP_H
#define ACTIONMAP_H

#include <GLFW/glfw3.h>
#include <cstdbool>
#include <glad/glad.h>
#include <map>
#include "Object.h"
#include "Key.h"
#include "Console.h"

class ActionMap :
    public Object
{
public:
    friend class Input;

    ActionMap();

    /// <summary>
    /// Adds an event to when the given key is first pressed.
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    void onKeyDown(const int key, void (*func)());

    /// <summary>
    /// Adds an event to when the given key is held down.
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    void onKeyPress(const int key, void (*func)());

    /// <summary>
    /// Adds an event to when the given key is released.
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    void onKeyUp(const int key, void (*func)());

private:
    std::map<int, void(*)()> keyDowns;
    std::map<int, void(*)()> keyPresses;
    std::map<int, void(*)()> keyUps;

    void logKeyDown(const int key);
    void logKeyPress(const int key);
    void logKeyUp(const int key);
};

#endif
