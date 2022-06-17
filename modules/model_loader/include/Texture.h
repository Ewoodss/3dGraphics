#pragma once

#include "glad/glad.h"
#include <string>
#include <unordered_map>

class Texture
{
private:
	GLuint id;
	inline static std::unordered_map<std::string, GLuint> textureCache;

	static GLuint loadTexture(const std::string& texturePath);

public:
	explicit Texture(const std::string& fileName);

	[[nodiscard]] GLuint getId() const;

	void bind();
};