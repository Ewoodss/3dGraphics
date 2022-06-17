//
// Created by Ewout on 16-6-2022.
//

#include "components/scripts/BulletScript.h"

#include <utility>

BulletScript::BulletScript(std::shared_ptr<Transform> parentTransform,
                           std::shared_ptr<Transform> selfTransform)
    : parentTransform(std::move(parentTransform)), selfTransform(std::move(selfTransform))
{
	auto rotation = this->parentTransform->getRotationDegrees();
	this->selfTransform->setRotationDegrees(rotation);
}

void BulletScript::Update()
{
	auto posistion = this->selfTransform->getPosition();
	posistion += this->selfTransform->get2DDirection();
	this->selfTransform->setPosition(posistion);

	if (glm::distance(parentTransform->getPosition(), selfTransform->getPosition()) > 1000)
	{
		selfTransform->setScale(glm::vec3(0, 0, 0));
		this->shouldBeRemoved = true;
	}
}