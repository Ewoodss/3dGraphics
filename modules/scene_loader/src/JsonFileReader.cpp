//
// Created by Ewout on 17-6-2022.
//

#include "JsonFileReader.h"
#include <json.hpp>
#include <fstream>

std::vector<FileReader::FileGameObject> JsonFileReader::GetFileGameObjects(const std::string& path) const
{
	std::vector<FileReader::FileGameObject> fileGameObjects;

	std::ifstream i(path);
	nlohmann::json jsonArray;

	i >> jsonArray;
	for (const auto& item : jsonArray)
	{
		FileReader::FileGameObject fileGameObject;
		item.at("modelName").get_to(fileGameObject.modelName);
		item.at("location").get_to(fileGameObject.location);
		item.at("rotation").get_to(fileGameObject.rotation);
		item.at("scale").get_to(fileGameObject.scale);
		fileGameObjects.push_back(fileGameObject);
	}
	return fileGameObjects;
}
