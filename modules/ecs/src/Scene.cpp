//
// Created by Ewout on 9-6-2022.
//

#include "Scene.h"
#include <iostream>

void Scene::Draw()
{
	for (const auto& gameObject : gameObjects)
	{
		gameObject->Draw();
	}
}

void Scene::Update()
{
	gameObjects.erase(remove_if(gameObjects.begin(), gameObjects.end(),
	                            [](const std::shared_ptr<GameObject>& gameObject) { return gameObject->GetShouldBeRemoved(); }),
	                  gameObjects.end());

	for (const auto& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::AddGameObject(const std::shared_ptr<GameObject>& gameObject)
{
	gameObjects.push_back(gameObject);
}

const glm::mat4& Scene::GetViewMatrix() const
{
	return viewMatrix;
}

Scene::Scene()
    : viewMatrix(glm::mat4(1.0f))
{
	inputSystem = std::make_shared<InputSystem>();
}

void Scene::SetViewMatrix(const glm::mat4& viewMatrix)
{
	this->viewMatrix = viewMatrix;
}

const std::shared_ptr<InputSystem>& Scene::GetInputSystemPtr() const
{
	return inputSystem;
}

InputSystem& Scene::GetInputSystem() const
{
	return *inputSystem;
}
