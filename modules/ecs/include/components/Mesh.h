//
// Created by Ewout on 14-6-2022.
//

#pragma once

#include "ModelCache.h"
#include "Transform.h"
#include <memory>

class Mesh : public Component
{
private:
	std::shared_ptr<Transform> transform;
	ModelCache::DrawAbles drawAbles;

public:
	Mesh(std::shared_ptr<Transform> transform, const std::string& filename);

	void Update() override;

private:
	void Draw() override;
};
