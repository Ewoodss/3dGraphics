//
// Created by Ewout on 9-6-2022.
//

#include "components/Transform.h"
#include "glm/trigonometric.hpp"

Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation,
                     const glm::vec3 &scale) : position(position),
                                               rotation(rotation),
                                               scale(scale) {}

glm::vec3 Transform::getRotationDegrees() const
{
    return glm::degrees(rotation);
}

const glm::vec3 &Transform::getRotation() const
{
    return rotation;
}

void Transform::setRotation(const glm::vec3 &newRotation)
{
    this->rotation = glm::radians(newRotation);
}

const glm::vec3 &Transform::getScale() const
{
    return scale;
}

void Transform::setScale(const glm::vec3 &newScale)
{
    this->scale = newScale;
}

const glm::vec3 &Transform::getPosition() const
{
    return position;
}

void Transform::setPosition(const glm::vec3 &newPosition)
{
    this->position = newPosition;
}

