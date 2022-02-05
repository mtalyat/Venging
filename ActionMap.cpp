#include "ActionMap.h"

ActionMap::ActionMap()
{
}

void ActionMap::onKeyDown(const int key, void(*func)())
{
    keyDowns[key] = func;
}

void ActionMap::onKeyPress(const int key, void(*func)())
{
    keyPresses[key] = func;
}

void ActionMap::onKeyUp(const int key, void(*func)())
{
    keyDowns[key] = func;
}

void ActionMap::logKeyDown(const int key)
{
    Console::Log("down");

    //check if the key exists
    if (keyDowns.find(key) != keyDowns.end())
    {
        //if it does, act upon it
        keyDowns[key]();
    }
}

void ActionMap::logKeyPress(const int key)
{
    Console::Log("press");

    //check if the key exists
    if (keyPresses.find(key) != keyPresses.end())
    {
        //if it does, act upon it
        keyPresses[key]();
    }
}

void ActionMap::logKeyUp(const int key)
{
    Console::Log("up");

    //check if the key exists
    if (keyUps.find(key) != keyUps.end())
    {
        //if it does, act upon it
        keyUps[key]();
    }
}
