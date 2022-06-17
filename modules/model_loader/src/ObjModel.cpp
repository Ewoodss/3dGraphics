#include "ObjModel.h"
#include "Texture.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <tigl.h>
#include <vector>

using tigl::Vertex;

/**
* Replaces a substring in a string
*/
static std::string Replace(std::string str, const std::string& toReplace, const std::string& replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

/**
* Splits a string into substrings, based on a seperator
*/
static std::vector<std::string> Split(std::string str, const std::string& seperator)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(seperator);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

/**
* Turns a string to lowercase
*/
static inline std::string ToLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

/**
* Cleans up a line for processing
*/
static inline std::string CleanLine(std::string line)
{
	line = Replace(line, "\t", " ");
	while (line.find("  ") != std::string::npos)
		line = Replace(line, "  ", " ");
	if (line.empty())
		return "";
	if (line[0] == ' ') { line = line.substr(1); }
	if (line.empty())
		return "";
	if (line[line.length() - 1] == ' ')
		line = line.substr(0, line.length() - 1);
	return line;
}

/**
* Loads an object model
*/
ObjModel::ObjModel(const std::string& fileName)
{
	std::cout << "Loading " << fileName << std::endl;
	std::string dirName = fileName;
	if (dirName.rfind('/') != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind('/'));
	if (dirName.rfind('\\') != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind('\\'));
	if (fileName == dirName)
		dirName = "";

	std::ifstream pFile(fileName.c_str());

	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}

	auto* currentGroup = new ObjGroup();
	currentGroup->MaterialIndex = -1;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = CleanLine(line);
		if (line.empty() || line[0] == '#')//skip empty or commented line
			continue;

		std::vector<std::string> params = Split(line, " ");
		params[0] = ToLower(params[0]);

		if (params[0] == "v")
			vertices.emplace_back(strtof(params[1].c_str(), nullptr),
			                      strtof(params[2].c_str(), nullptr),
			                      strtof(params[3].c_str(), nullptr));
		else if (params[0] == "vn")
			normals.emplace_back(strtof(params[1].c_str(), nullptr),
			                     strtof(params[2].c_str(), nullptr),
			                     strtof(params[3].c_str(), nullptr));
		else if (params[0] == "vt")
			texcoords.emplace_back(strtof(params[1].c_str(), nullptr),
			                       strtof(params[2].c_str(), nullptr));
		else if (params[0] == "f")
		{
			for (size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for (size_t i = ii - 3; i < ii; i++)//magische forlus om van quads triangles te maken ;)
				{
					Vertex vertex{};
					std::vector<std::string> indices = Split(params[i == (ii - 3) ? 1 : i], "/");
					if (!indices.empty())//er is een positie
						vertex.Position = strtol(indices[0].c_str(), nullptr, 10) - 1;
					if (indices.size() == 2)//alleen texture
						vertex.Texcoord = strtol(indices[1].c_str(), nullptr, 10) - 1;
					if (indices.size() == 3)//v/t/n of v//n
					{
						if (!indices[1].empty())
							vertex.Texcoord = strtol(indices[1].c_str(), nullptr, 10) - 1;
						vertex.Normal = strtol(indices[2].c_str(), nullptr, 10) - 1;
					}
					face.Vertices.push_back(vertex);
				}
				currentGroup->Faces.push_back(face);
			}
		}
		else if (params[0] == "s")
		{//smoothing groups
		}
		else if (params[0] == "mtllib")
		{
			LoadMaterialFile(dirName + "/" + params[1], dirName);
		}
		else if (params[0] == "usemtl")
		{
			if (!currentGroup->Faces.empty())
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->MaterialIndex = -1;

			for (int i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if (info->Name == params[1])
				{
					currentGroup->MaterialIndex = i;
					break;
				}
			}
			if (currentGroup->MaterialIndex == -1)
				std::cout << "Could not find material name " << params[1] << std::endl;
		}
	}
	groups.push_back(currentGroup);

	MakeVbo();
}

ObjModel::~ObjModel() = default;

void ObjModel::Draw()
{
	//foreach group in groups
	//  set material texture, if available
	//  set material color, if available
	//  foreach face in group
	//    foreach vertex in face
	//      emit vertex

	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::shader->enableTexture(true);

	for (const auto& group : groups)
	{
		if (group->MaterialIndex != -1)
		{
			auto texture = materials[group->MaterialIndex]->Texture;
			if (texture) texture->Bind();
		}

		tigl::drawVertices(GL_TRIANGLES, group->Vbo.get());
	}
	tigl::shader->enableTexture(false);
}

void ObjModel::LoadMaterialFile(const std::string& fileName, const std::string& dirName)
{
	std::cout << "Loading " << fileName << std::endl;
	std::ifstream pFile(fileName.c_str());
	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}

	MaterialInfo* currentMaterial = nullptr;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = CleanLine(line);
		if (line.empty() || line[0] == '#')
			continue;

		std::vector<std::string> params = Split(line, " ");
		params[0] = ToLower(params[0]);

		if (params[0] == "newmtl")
		{
			if (currentMaterial != nullptr)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->Name = params[1];
		}
		else if (params[0] == "map_kd")
		{
			std::string tex = params[1];
			if (tex.find('/'))
				tex = tex.substr(tex.rfind('/') + 1);
			if (tex.find('\\'))
				tex = tex.substr(tex.rfind('\\') + 1);
			//TODO
			if (currentMaterial != nullptr)
			{
				auto textureDir = dirName;
				currentMaterial->Texture = new Texture(textureDir.append("/").append(tex));
			}
		}
		else if (params[0] == "kd")
		{
			//TODO, diffuse color
		}
		else if (params[0] == "ka")
		{
			//TODO, ambient color
		}
		else if (params[0] == "ks")
		{
			//TODO, specular color
		}
		else if (
		        params[0] == "illum" || params[0] == "map_bump" || params[0] == "map_ke" || params[0] == "map_ka" || params[0] == "map_d" || params[0] == "d" || params[0] == "ke" || params[0] == "ns" || params[0] == "ni" || params[0] == "td" || params[0] == "tf" || params[0] == "tr")
		{
			//these values are usually not used for rendering at this time, so ignore them
		}
		else { std::cout << "Didn't parse " << params[0] << " in material file" << std::endl; }
	}

	if (currentMaterial != nullptr)
		materials.push_back(currentMaterial);
}

void ObjModel::MakeVbo()
{
	for (auto& objGroup : groups)
	{
		std::vector<tigl::Vertex> groupVertices;
		for (const auto& face : objGroup->Faces)
		{

			for (const auto& vertex : face.Vertices)
			{
				auto vertexPosition = this->vertices[vertex.Position];
				auto normalPosition = this->normals[vertex.Normal];
				auto texturePosition = this->texcoords[vertex.Texcoord];
				auto loadedVertex = tigl::Vertex::PTN(vertexPosition, texturePosition, normalPosition);
				groupVertices.push_back(loadedVertex);
			}
		}
		std::shared_ptr<tigl::VBO> vboPtr(tigl::createVbo(groupVertices));
		objGroup->Vbo = vboPtr;
	}
	FillDrawables();
}

void ObjModel::FillDrawables()
{
	for (const auto& group : groups)
	{
		Drawable drawable;
		drawable.Vbo = group->Vbo;
		drawable.TextureId = -1;
		if (group->MaterialIndex != -1)
		{
			auto texture = materials[group->MaterialIndex]->Texture;
			if (texture) drawable.TextureId = texture->GetId();
		}
		drawables.push_back(drawable);
	}
}

// absolut *** code this should have been different
const std::vector<ObjModel::Drawable>& ObjModel::GetDrawables()
{
	for (auto& item : groups)
	{
		item->Faces.clear();
	}
	groups.clear();

	return drawables;
}

ObjModel::MaterialInfo::MaterialInfo()
{
	Texture = nullptr;
}
