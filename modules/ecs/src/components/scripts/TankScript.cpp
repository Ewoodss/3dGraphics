//
// Created by Ewout on 16-6-2022.
//

#include "components/scripts/TankScript.h"
#include "GLFW/glfw3.h"
#include "GameTimer.h"
#include "glm/geometric.hpp"

#include <utility>
#include <iostream>


TankScript::TankScript(std::shared_ptr<InputSystem> inputSystem, std::shared_ptr<Transform> transform)
        : inputSystem(std::move(inputSystem)), transform(std::move(transform))
{
    this->inputSystem->addKeyFunction(GLFW_KEY_W, [this](int action) { this->moveForward(action); });
    this->inputSystem->addKeyFunction(GLFW_KEY_S, [this](int action) { this->moveBackward(action); });
    this->inputSystem->addKeyFunction(GLFW_KEY_A, [this](int action) { this->rotateLeft(action); });
    this->inputSystem->addKeyFunction(GLFW_KEY_D, [this](int action) { this->rotateRight(action); });

}


void TankScript::moveForward(int action)
{
    std::cout << "Forward" << action << std::endl;
    if (action == GLFW_PRESS) movement.moveForward = true;
    if (action == GLFW_RELEASE) movement.moveForward = false;

}

void TankScript::moveBackward(int action)
{
    if (action == GLFW_PRESS) movement.moveBackward = true;
    if (action == GLFW_RELEASE) movement.moveBackward = false;

}

double testing = 0.0f;

void TankScript::Update()
{
    auto position = transform->getPosition();
    auto rotation = transform->getRotationDegrees();
    auto deltaTime = GameTimer::getDeltaTime();
    testing += deltaTime;

    std::cout << "deltaTime: " << testing << std::endl;
    auto direction = transform->get2DDirection() * 0.05f;

    if (movement.moveForward) position += direction;
    if (movement.moveBackward) position -= direction;
    if (movement.rotateLeft) rotation.y += 0.5f;
    if (movement.rotateRight) rotation.y -= 0.5f;
    
    transform->setPosition(position);
    transform->setRotationDegrees(rotation);
}

void TankScript::rotateLeft(int action)
{
    if (action == GLFW_PRESS) movement.rotateLeft = true;
    if (action == GLFW_RELEASE) movement.rotateLeft = false;

}

void TankScript::rotateRight(int action)
{
    if (action == GLFW_PRESS) movement.rotateRight = true;
    if (action == GLFW_RELEASE) movement.rotateRight = false;
}
