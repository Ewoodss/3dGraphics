//
// Created by Ewout on 9-6-2022.
//

#pragma once

#include "GameObject.h"
#include "InputSystem.h"
#include "glm/glm.hpp"
#include "interfaces/DrawAble.h"
#include "interfaces/UpdateAble.h"
#include <memory>
#include <vector>

class Scene : public UpdateAble, public DrawAble
{
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	glm::mat4 viewMatrix;
	std::shared_ptr<InputSystem> inputSystem;

public:
	void Draw() override;

	void Update() override;

	void AddGameObject(const std::shared_ptr<GameObject>&);

	[[nodiscard]] const glm::mat4& GetViewMatrix() const;

	void SetViewMatrix(const glm::mat4& viewMatrix);

	Scene();

	[[nodiscard]] InputSystem& GetInputSystem() const;

	[[nodiscard]] const std::shared_ptr<InputSystem>& GetInputSystemPtr() const;
};
