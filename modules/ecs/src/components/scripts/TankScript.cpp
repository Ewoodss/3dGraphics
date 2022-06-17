//
// Created by Ewout on 16-6-2022.
//

#include "components/scripts/TankScript.h"
#include "components/Mesh.h"
#include "components/scripts/BulletScript.h"
#include "glm/geometric.hpp"

#include "GLFW/glfw3.h"
#include <utility>

TankScript::TankScript(std::shared_ptr<Scene> scene,
                       std::shared_ptr<Transform> transform)
    : scene(std::move(scene)), transform(std::move(transform))
{
	this->inputSystem = this->scene->getInputSystemPtr();

	this->inputSystem->addKeyFunction(GLFW_KEY_W, [this](int action) { this->moveForward(action); });
	this->inputSystem->addKeyFunction(GLFW_KEY_S, [this](int action) { this->moveBackward(action); });
	this->inputSystem->addKeyFunction(GLFW_KEY_A, [this](int action) { this->rotateLeft(action); });
	this->inputSystem->addKeyFunction(GLFW_KEY_D, [this](int action) { this->rotateRight(action); });
	this->inputSystem->addKeyFunction(GLFW_KEY_SPACE, [this](int action) { this->shoot(action); });
}

void TankScript::moveForward(int action)
{
	if (action == GLFW_PRESS) movement.moveForward = true;
	if (action == GLFW_RELEASE) movement.moveForward = false;
}

void TankScript::moveBackward(int action)
{
	if (action == GLFW_PRESS) movement.moveBackward = true;
	if (action == GLFW_RELEASE) movement.moveBackward = false;
}

void TankScript::Update()
{
	auto position = transform->getPosition();
	auto rotation = transform->getRotationDegrees();

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

void TankScript::shoot(int action)
{
	auto bulletGameObject = std::make_shared<GameObject>();
	auto bulletTransform = bulletGameObject->AddComponent<Transform>(transform->getPosition() + glm::vec3(0, 1, 0));

	bulletGameObject->AddComponent<Mesh>(bulletTransform, "../resource/models/shell/TankShell.obj");
	bulletGameObject->AddComponent<BulletScript>(transform, bulletTransform);

	scene->AddGameObject(bulletGameObject);
}
