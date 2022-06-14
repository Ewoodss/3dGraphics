//
// Created by Ewout on 14-6-2022.
//

#pragma once

#include "Transform.h"
#include "ObjModel.h"
#include <memory>

class Mesh : public Component
{
private:
    std::shared_ptr<Transform> transform;
    std::shared_ptr<ObjModel> model;

public:
    Mesh(std::shared_ptr<Transform> transform, std::shared_ptr<ObjModel> model);

    Mesh(std::shared_ptr<Transform> transform, const std::string &filename);

private:
    void Draw() override;


};
