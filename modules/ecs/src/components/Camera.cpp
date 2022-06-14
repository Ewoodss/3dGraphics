//
// Created by Ewout on 14-6-2022.
//

#include "components/Camera.h"
#include "glm/ext/matrix_transform.hpp"

#include <utility>


void Camera::Draw()
{


}

void Camera::Update()
{
    glm::vec3 Up(0.0, 1.0f, 0.0f);
    auto viewFrom = parentTransform->getPosition() + offsetTransform->getPosition() + glm::vec3(0.0f, 2.0f, 0.0f);


    auto viewAt = viewFrom + glm::vec3(0.0f, -0.5f, 1.0f);

    glm::mat4 viewMatrix = glm::lookAt(viewFrom, viewAt, Up);


    scene->setViewMatrix(viewMatrix);
}

Camera::Camera(std::shared_ptr<Scene> scene, std::shared_ptr<Transform> parentTransform,
               std::shared_ptr<Transform> offsetTransform) : scene(std::move(scene)),
                                                             parentTransform(std::move(parentTransform)),
                                                             offsetTransform(std::move(offsetTransform)) {}

Camera::Camera(std::shared_ptr<Scene> scene, std::shared_ptr<Transform> parentTransform) : scene(std::move(scene)),
                                                                                           parentTransform(std::move(
                                                                                                   parentTransform))
{
    offsetTransform = std::make_shared<Transform>(glm::vec3(0.0f, 1.0f, 0.0f));
}

