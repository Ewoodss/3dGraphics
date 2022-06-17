//
// Created by Ewout on 16-6-2022.
//

#include "components/scripts/BulletScript.h"

#include <utility>

BulletScript::BulletScript(std::shared_ptr<Transform> parentTransform,
                           std::shared_ptr<Transform> selfTransform)
    : parentTransform(std::move(parentTransform)), SelfTransform(std::move(selfTransform))
{
	auto rotation = this->parentTransform->getRotationDegrees();
	this->SelfTransform->setRotationDegrees(rotation);
}

void BulletScript::Update()
{
	auto posistion = this->SelfTransform->getPosition();
	posistion += this->SelfTransform->get2DDirection();
	this->SelfTransform->setPosition(posistion);

	if (glm::distance(parentTransform->getPosition(), SelfTransform->getPosition()) > 1000)
	{
		SelfTransform->setScale(glm::vec3(0, 0, 0));
		this->shouldBeRemoved = true;
	}
}