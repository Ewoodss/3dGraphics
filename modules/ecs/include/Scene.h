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
	bool RemoveGameObject(const std::shared_ptr<GameObject>&);
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	glm::mat4 viewMatrix;
	std::shared_ptr<InputSystem> inputSystem;

public:
	void Draw() override;

	void Update() override;

	void AddGameObject(const std::shared_ptr<GameObject>&);

	[[nodiscard]] const glm::mat4& getViewMatrix() const;

	void setViewMatrix(const glm::mat4& viewMatrix);

	Scene();

	[[nodiscard]] InputSystem& getInputSystem() const;

	[[nodiscard]] const std::shared_ptr<InputSystem>& getInputSystemPtr() const;
};
