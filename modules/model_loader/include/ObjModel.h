#pragma once

#include "glm/glm.hpp"

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <tigl.h>

class Texture;

class ObjModel
{
private:
    inline static std::unordered_map<std::string, ObjModel *> modelCache;

    explicit ObjModel(const std::string &filename);

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
        Texture *texture;
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
    std::vector<ObjGroup *> groups;
    std::vector<MaterialInfo *> materials;

    void loadMaterialFile(const std::string &fileName, const std::string &dirName);

    void MakeVbo();


    void fillDrawables();

public:
    ~ObjModel();

    static ObjModel *getObjModel(const std::string &filename);

    void Draw();

    struct Drawable
    {
        std::shared_ptr<tigl::VBO> vbo;
        GLuint textureId;
    };

    const std::vector<Drawable> &getDrawables() const;

private:
    std::vector<Drawable> drawables;


};

