//
// Created by Ewout on 16-6-2022.
//

#pragma once

#include <functional>
#include <map>

class InputSystem
{
private:
	std::unordered_map<int, std::function<void(int action)>> keyFunctionMap;

public:
	/**
 *
 * @param key the key which need to trigger the function
 * @param function the function that needs to be called when pressing the specified key
 * @return returns a boolean indicating if the keyFunction was added
 */
	bool AddKeyFunction(int key, const std::function<void(int action)>& function);

	/**
     *
     * @param key the key which is pressed to trigger a function
     * @param action  indicating which action is performed, can be pressed, released, repeated or any arbitrary number if not using in combination with glfw keys
     * @return returns whether or not the matching key function exists
     */
	bool TriggerKeyFunction(int key, int action) const;

	/**
     * @param key the key which needs to be removed
     * @return returns whether or not the matching keyFunction is removed
     */
	bool RemoveKeyFunction(int key);
};
