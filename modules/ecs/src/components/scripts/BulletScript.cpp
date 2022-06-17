//
// Created by Ewout on 16-6-2022.
//

#include "components/scripts/BulletScript.h"

#include <utility>

BulletScript::BulletScript(std::shared_ptr<Transform> parentTransform,
                           std::shared_ptr<Transform> selfTransform)
    : parentTransform(std::move(parentTransform)), selfTransform(std::move(selfTransform))
{
	auto rotation = this->parentTransform->GetRotationDegrees();
	this->selfTransform->SetRotationDegrees(rotation);
}

void BulletScript::Update()
{
	auto position = this->selfTransform->GetPosition();
	position += this->selfTransform->Get2DDirection();
	this->selfTransform->SetPosition(position);

	if (glm::distance(parentTransform->GetPosition(), selfTransform->GetPosition()) > 1000)
	{
		selfTransform->SetScale(glm::vec3(0, 0, 0));
		this->ShouldBeRemoved = true;
	}
}