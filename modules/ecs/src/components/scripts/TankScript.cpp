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
	this->inputSystem = this->scene->GetInputSystemPtr();

	this->inputSystem->AddKeyFunction(GLFW_KEY_W, [this](int action) { this->MoveForward(action); });
	this->inputSystem->AddKeyFunction(GLFW_KEY_S, [this](int action) { this->MoveBackward(action); });
	this->inputSystem->AddKeyFunction(GLFW_KEY_A, [this](int action) { this->RotateLeft(action); });
	this->inputSystem->AddKeyFunction(GLFW_KEY_D, [this](int action) { this->RotateRight(action); });
	this->inputSystem->AddKeyFunction(GLFW_KEY_SPACE, [this](int action) { this->Shoot(action); });
}

void TankScript::MoveForward(int action)
{
	if (action == GLFW_PRESS) movement.MoveForward = true;
	if (action == GLFW_RELEASE) movement.MoveForward = false;
}

void TankScript::MoveBackward(int action)
{
	if (action == GLFW_PRESS) movement.MoveBackward = true;
	if (action == GLFW_RELEASE) movement.MoveBackward = false;
}

void TankScript::Update()
{
	auto position = transform->GetPosition();
	auto rotation = transform->GetRotationDegrees();

	auto direction = transform->Get2DDirection() * 0.05f;

	if (movement.MoveForward) position += direction;
	if (movement.MoveBackward) position -= direction;
	if (movement.RotateLeft) rotation.y += 0.5f;
	if (movement.RotateRight) rotation.y -= 0.5f;

	transform->SetPosition(position);
	transform->SetRotationDegrees(rotation);
}

void TankScript::RotateLeft(int action)
{
	if (action == GLFW_PRESS) movement.RotateLeft = true;
	if (action == GLFW_RELEASE) movement.RotateLeft = false;
}

void TankScript::RotateRight(int action)
{
	if (action == GLFW_PRESS) movement.RotateRight = true;
	if (action == GLFW_RELEASE) movement.RotateRight = false;
}

void TankScript::Shoot(int)
{
	auto bulletGameObject = std::make_shared<GameObject>();
	auto bulletTransform = bulletGameObject->AddComponent<Transform>(transform->GetPosition() + glm::vec3(0, 1, 0));

	bulletGameObject->AddComponent<Mesh>(bulletTransform, "../resource/models/shell/TankShell.obj");
	bulletGameObject->AddComponent<BulletScript>(transform, bulletTransform);

	scene->AddGameObject(bulletGameObject);
}
