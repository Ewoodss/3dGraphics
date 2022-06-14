//
// Created by Ewout on 12-5-2022.
//

#pragma once

#include "glm/glm.hpp"

struct GLFWwindow;

class FpsCam
{
public:
    explicit FpsCam(GLFWwindow *);

    glm::mat4 getMatrix();

    void update(GLFWwindow *);

private:
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec2 rotation = glm::vec2(0, 0);

    void move(float angle, float fac);
};
