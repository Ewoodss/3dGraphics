#pragma once


#include <string>
#include <GL/gl.h>

class Texture {
    GLuint id;
public:
    Texture(const std::string &fileName);

    void bind();
};