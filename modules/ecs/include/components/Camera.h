//
// Created by Ewout on 14-6-2022.
//

#pragma once

#include <memory>
#include "Scene.h"
#include "Transform.h"

class Camera : public Component
{
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Transform> parentTransform;
    std::shared_ptr<Transform> offsetTransform;

public:
    Camera(std::shared_ptr<Scene> scene, std::shared_ptr<Transform> parentTransform,
           std::shared_ptr<Transform> offsetTransform);

    Camera(std::shared_ptr<Scene> scene, std::shared_ptr<Transform> parentTransform);


private:
    void Draw() override;

    void Update() override;

};
