//
// Created by Ewout on 16-6-2022.
//

#pragma once


#include <map>
#include <functional>

class InputSystem
{
private:
    std::unordered_map<int, std::function<void(int action)>> keyFunctionMap;

public:
    bool addKeyFunction(int key, const std::function<void(int action)> &function);

    bool triggerKeyFunction(int key, int action) const;

    bool removeKeyFunction(int key);

};


