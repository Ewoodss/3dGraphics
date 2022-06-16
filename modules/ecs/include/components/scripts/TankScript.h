//
// Created by Ewout on 16-6-2022.
//

#pragma once

#include <memory>
#include "InputSystem.h"
#include "Component.h"
#include "components/Transform.h"


class TankScript : public Component
{
private:
    std::shared_ptr<InputSystem> inputSystem;
    std::shared_ptr<Transform> transform;

    struct Movement
    {
        bool moveForward;
        bool moveBackward;
        bool rotateLeft;
        bool rotateRight;
    };

    Movement movement = {false, false, false, false};


    void moveForward(int action);

    void moveBackward(int action);

    void rotateLeft(int action);

    void rotateRight(int action);


public:
    TankScript(std::shared_ptr<InputSystem> inputSystem, std::shared_ptr<Transform> transform);

    void Update() override;
};


