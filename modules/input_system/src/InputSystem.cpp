//
// Created by Ewout on 16-6-2022.
//

#include "InputSystem.h"


bool InputSystem::addKeyFunction(int key, const std::function<void(int action)> &function)
{
    auto inserted = keyFunctionMap.emplace(key, function);

    return inserted.second;
}

bool InputSystem::triggerKeyFunction(int key, int action) const
{
    auto functionFound = keyFunctionMap.find(key);
    if (functionFound == keyFunctionMap.end()) return false;

    functionFound->second(action);

    return true;
}

bool InputSystem::removeKeyFunction(int key)
{
    return keyFunctionMap.erase(key);
}



