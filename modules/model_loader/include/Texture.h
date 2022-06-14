#pragma once


#include <string>
#include <unordered_map>
#include "glad/glad.h"

class Texture
{
private:
    GLuint id;
    inline static std::unordered_map<std::string, GLuint> textureCache;

    static GLuint loadTexture(const std::string &texturePath);

public:
    explicit Texture(const std::string &fileName);

    GLuint getId() const;

    void bind();
};