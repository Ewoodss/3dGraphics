//
// Created by Ewout on 16-6-2022.
//

#include "InputSystem.h"

bool InputSystem::AddKeyFunction(int key, const std::function<void(int action)>& function)
{
	auto inserted = keyFunctionMap.emplace(key, function);

	return inserted.second;
}

bool InputSystem::TriggerKeyFunction(int key, int action) const
{
	auto functionFound = keyFunctionMap.find(key);
	if (functionFound == keyFunctionMap.end()) return false;

	functionFound->second(action);

	return true;
}

bool InputSystem::RemoveKeyFunction(int key)
{
	return keyFunctionMap.erase(key);
}
