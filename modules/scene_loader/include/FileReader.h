//
// Created by Ewout on 17-6-2022.
//


#pragma once

#include <string>
#include <vector>

class FileReader
{
public:
	struct FileGameObject
	{
		std::string ModelName;
		float Location[3];
		float Rotation[3];
		float Scale[3];
	};

	[[nodiscard]] virtual std::vector<FileGameObject> GetFileGameObjects(const std::string& path) const = 0;

};
