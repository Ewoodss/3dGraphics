#include "Texture.h"
#include "tigl.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include <iostream>
#include <stb_image.h>

Texture::Texture(const std::string& fileName)
{
	std::cout << "opening texture " << fileName << std::endl;
	auto texture = textureCache.find(fileName);

	if (texture != textureCache.end())
	{
		id = texture->second;
	}
	else
	{
		auto textureGluint = loadTexture(fileName);

		textureCache.insert({fileName, textureGluint});

		id = textureGluint;
	}
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
	// tigl::shader->enableTexture(true);
}

GLuint Texture::loadTexture(const std::string& texturePath)
{
	std::cout << "loading texture " << texturePath << std::endl;
	int width, height, bpp;
	stbi_set_flip_vertically_on_load(true);
	auto* imgData = stbi_load(texturePath.c_str(), &width, &height, &bpp, 4);

	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, imgData);
	stbi_image_free(imgData);

	return textureId;
}

GLuint Texture::getId() const
{
	return id;
}
