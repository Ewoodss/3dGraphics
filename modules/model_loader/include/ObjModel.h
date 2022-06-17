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
		int Position;
		int Normal;
		int Texcoord;
	};

	class Face
	{
	public:
		std::list<Vertex> Vertices;
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();

		std::string Name;
		Texture* Texture;
	};

	class ObjGroup
	{
	public:
		std::string Name;
		int MaterialIndex;
		std::list<Face> Faces;
		std::shared_ptr<tigl::VBO> Vbo;
	};

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void LoadMaterialFile(const std::string& fileName, const std::string& dirName);

	void MakeVbo();

	void FillDrawables();

public:
	~ObjModel();

	void Draw();

	explicit ObjModel(const std::string& filename);

	struct Drawable {
		std::shared_ptr<tigl::VBO> Vbo;
		GLuint TextureId;
	};

	const std::vector<Drawable>& GetDrawables();

private:
	std::vector<Drawable> drawables;
};
