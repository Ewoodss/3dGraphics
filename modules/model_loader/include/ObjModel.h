#pragma once

#include "glm/glm.hpp"

#include <list>
#include <memory>
#include <string>
#include <tigl.h>
#include <unordered_map>
#include <vector>

class Texture;

class ObjModel
{
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		std::list<Vertex> vertices;
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();

		std::string name;
		Texture* texture;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
		std::shared_ptr<tigl::VBO> vbo;
	};

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void loadMaterialFile(const std::string& fileName, const std::string& dirName);

	void MakeVbo();

	void fillDrawables();

public:
	~ObjModel();

	void Draw();

	explicit ObjModel(const std::string& filename);

	struct Drawable {
		std::shared_ptr<tigl::VBO> vbo;
		GLuint textureId;
	};

	const std::vector<Drawable>& getDrawables();

private:
	std::vector<Drawable> drawables;
};
