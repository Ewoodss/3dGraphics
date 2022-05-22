//
// Created by Ewout on 12-5-2022.
//

#ifndef INC_3DGRAPHICS_FPSCAM_H
#define INC_3DGRAPHICS_FPSCAM_H

#include "glm/glm.hpp"

struct GLFWwindow;

class FpsCam {
public:
    FpsCam(GLFWwindow*);

    glm::mat4 getMatrix();
    void update(GLFWwindow*);

private:
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec2 rotation = glm::vec2(0, 0);

    void move(float angle, float fac);
};


#endif //INC_3DGRAPHICS_FPSCAM_H