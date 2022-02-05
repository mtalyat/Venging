#include "ActionMap.h"

ActionMap::ActionMap()
{
}

void ActionMap::onKeyDown(const int key, std::function<void()> func)
{
    keyDowns[key] = func;
}

void ActionMap::onKeyPress(const int key, std::function<void()> func)
{
    keyPresses[key] = func;
}

void ActionMap::onKeyUp(const int key, std::function<void()> func)
{
    keyUps[key] = func;
}

void ActionMap::logKeyDown(const int key)
{
    //check if the key exists
    if (keyDowns.find(key) != keyDowns.end())
    {
        //if it does, act upon it
        keyDowns[key]();
    }
}

void ActionMap::logKeyPress(const int key)
{
    //check if the key exists
    if (keyPresses.find(key) != keyPresses.end())
    {
        //if it does, act upon it
        keyPresses[key]();
    }
}

void ActionMap::logKeyUp(const int key)
{
    //check if the key exists
    if (keyUps.find(key) != keyUps.end())
    {
        //if it does, act upon it
        keyUps[key]();
    }
}
