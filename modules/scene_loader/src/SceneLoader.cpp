//
// Created by Ewout on 17-6-2022.
//

#include "SceneLoader.h"
#include "FileReaderFactory.h"
#include "components/Mesh.h"
#include "components/Transform.h"
#include <glm/gtc/type_ptr.hpp>

void SceneLoader::LoadScene(const std::shared_ptr<Scene>& scene, const std::string& filename)
{
	FileReaderFactory::FileType filetype = FileReaderFactory::FileType::none;
	if (filename.find("json") != std::string::npos)
	{
		filetype = FileReaderFactory::FileType::json;
		std::cout << "json file type!" << '\n';
	}
	if (filename.find("txt") != std::string::npos)
	{
		filetype = FileReaderFactory::FileType::txt;
		std::cout << "txt file type!" << '\n';
	}
	if (filetype == FileReaderFactory::FileType::none) return;
	auto fileReader = FileReaderFactory::GetFileReader(filetype);
	auto fileGameObjects = fileReader->GetFileGameObjects(filename);

	for (const auto& fileGameObject : fileGameObjects)
	{
		auto gameObject = std::make_shared<GameObject>();
		auto transform = gameObject->AddComponent<Transform>(glm::make_vec3(fileGameObject.Location),
		                                                     glm::make_vec3(fileGameObject.Rotation), glm::make_vec3(fileGameObject.Scale));
		gameObject->AddComponent<Mesh>(transform, fileGameObject.ModelName);
		scene->AddGameObject(gameObject);
	}
}
