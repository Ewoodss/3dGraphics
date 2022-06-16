//
// Created by Ewout on 9-6-2022.
//

#include "Scene.h"

void Scene::Draw()
{
    for (const auto &gameObject: gameObjects)
    {
        gameObject->Draw();
    }
}

void Scene::Update()
{
    for (const auto &gameObject: gameObjects)
    {
        gameObject->Update();
    }
}

void Scene::AddGameObject(const std::shared_ptr<GameObject> &gameObject)
{
    gameObjects.push_back(gameObject);
}

const glm::mat4 &Scene::getViewMatrix() const
{
    return viewMatrix;
}

Scene::Scene() : viewMatrix(glm::mat4(1.0f))
{
    inputSystem = std::make_shared<InputSystem>();
}

void Scene::setViewMatrix(const glm::mat4 &newViewMatrix)
{
    viewMatrix = newViewMatrix;
}

const std::shared_ptr<InputSystem> &Scene::getInputSystemPtr() const
{
    return inputSystem;
}

InputSystem &Scene::getInputSystem() const
{
    return *inputSystem;
}

