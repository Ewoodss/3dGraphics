//
// Created by Ewout on 16-6-2022.
//

#pragma once

#include "Component.h"
#include "Scene.h"
#include "components/Transform.h"

class BulletScript : public Component
{
private:
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Transform> parentTransform;
	std::shared_ptr<Transform> SelfTransform;

	void Update() override;

public:
	BulletScript(std::shared_ptr<Transform> parentTransform,
	             std::shared_ptr<Transform> selfTransform);
};
