//
// Created by Ewout on 16-6-2022.
//

#pragma once

#include "Component.h"
#include "InputSystem.h"
#include "Scene.h"
#include "components/Transform.h"
#include <memory>

class TankScript : public Component
{
private:
	std::shared_ptr<InputSystem> inputSystem;
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Transform> transform;

	struct Movement {
		bool MoveForward;
		bool MoveBackward;
		bool RotateLeft;
		bool RotateRight;
	};

	Movement movement = {false, false, false, false};

	void MoveForward(int action);

	void MoveBackward(int action);

	void RotateLeft(int action);

	void RotateRight(int action);

	void Shoot(int action);

public:
	TankScript(std::shared_ptr<Scene> scene,
	           std::shared_ptr<Transform> transform);

	void Update() override;
};
