//
// Created by Ewout on 9-6-2022.
//

#pragma once

#include "glm/vec3.hpp"
#include "Component.h"

class Transform : public Component
{
private:
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 position;


public:
    explicit Transform(const glm::vec3 &position, const glm::vec3 &rotation = glm::vec3(0, 0, 0),
                       const glm::vec3 &scale = glm::vec3(1, 1, 1));

    glm::vec3 getRotationDegrees() const;

    void setRotation(const glm::vec3 &rotation);

    const glm::vec3 &getScale() const;

    void setScale(const glm::vec3 &scale);

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getRotation() const;

};
