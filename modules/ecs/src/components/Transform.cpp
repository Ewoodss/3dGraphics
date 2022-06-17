//
// Created by Ewout on 9-6-2022.
//

#include "components/Transform.h"
#include "glm/trigonometric.hpp"

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation,
                     const glm::vec3& scale)
    : position(position),
      rotation(rotation),
      scale(scale)
{
}

glm::vec3 Transform::GetRotationDegrees() const
{
	return glm::degrees(rotation);
}

const glm::vec3& Transform::GetRotation() const
{
	return rotation;
}

[[maybe_unused]] void Transform::SetRotation(const glm::vec3& rotation)
{
	Transform::rotation = rotation;
}

void Transform::SetRotationDegrees(const glm::vec3& newRotation)
{
	this->rotation = glm::radians(newRotation);
}

const glm::vec3& Transform::GetScale() const
{
	return scale;
}

void Transform::SetScale(const glm::vec3& scale)
{
	this->scale = scale;

	if (this->scale == glm::vec3(0, 0, 0)) ShouldBeRemoved = true;//not the best way to do this, but it works
}

const glm::vec3& Transform::GetPosition() const
{
	return position;
}

void Transform::SetPosition(const glm::vec3& position)
{
	this->position = position;
}

glm::vec3 Transform::Get2DDirection() const
{
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
	direction.x += sinf(rotation.y);
	direction.z += cosf(rotation.y);
	return direction;
}
