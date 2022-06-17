//
// Created by Ewout on 14-6-2022.
//

#include <memory>
#include <utility>
#include "components/Mesh.h"
#include "glm/gtc/matrix_transform.hpp"

void Mesh::Draw()
{
//    model->Draw();
	glm::mat4 modelMatrix(1.0f);

	auto rotation = transform->getRotation();

	modelMatrix = glm::translate(modelMatrix, transform->getPosition());
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));

	modelMatrix = glm::scale(modelMatrix, transform->getScale());

	tigl::shader->setModelMatrix(modelMatrix);

	tigl::shader->enableTexture(true);

	for (const auto& drawable : this->drawAbles)
	{
		if (drawable.textureId != -1) glBindTexture(GL_TEXTURE_2D, drawable.textureId);
		tigl::drawVertices(GL_TRIANGLES, drawable.vbo.get());
	}

	tigl::shader->enableTexture(false);
}

Mesh::Mesh(std::shared_ptr<Transform> transform, const std::string& filename)
		:transform(std::move(transform))
{
	this->drawAbles = ModelCache::getObjModel(filename);
}
void Mesh::Update()
{
	if (transform->ShouldBeRemoved())
	{
		this->shouldBeRemoved = true;
	}
}
