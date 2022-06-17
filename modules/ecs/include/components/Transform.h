//
// Created by Ewout on 9-6-2022.
//

#pragma once

#include "Component.h"
#include "glm/vec3.hpp"

class Transform : public Component
{
private:
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 position;

public:
	explicit Transform(const glm::vec3& position,
	                   const glm::vec3& rotation = glm::vec3(0, 0, 0),
	                   const glm::vec3& scale = glm::vec3(1, 1, 1));

	[[nodiscard]] glm::vec3 getRotationDegrees() const;

	void setRotationDegrees(const glm::vec3& newRotation);

	[[nodiscard]] const glm::vec3& getScale() const;

	void setScale(const glm::vec3& scale);

	[[nodiscard]] const glm::vec3& getPosition() const;

	void setPosition(const glm::vec3& position);

	[[nodiscard]] const glm::vec3& getRotation() const;

	[[nodiscard]] glm::vec3 get2DDirection() const;

	[[maybe_unused]] void setRotation(const glm::vec3& rotation);
};
