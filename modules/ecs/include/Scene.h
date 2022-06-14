//
// Created by Ewout on 9-6-2022.
//

#pragma once

#include "GameObject.h"
#include "interfaces/UpdateAble.h"
#include "interfaces/DrawAble.h"
#include <vector>
#include <memory>
#include "glm/glm.hpp"

class Scene : public UpdateAble, public DrawAble
{
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    glm::mat4 viewMatrix;

public:
    void Draw() override;

    void Update() override;

    void AddGameObject(const std::shared_ptr<GameObject> &);

    const glm::mat4 &getViewMatrix() const;

    void setViewMatrix(const glm::mat4 &viewMatrix);

    Scene();


};

