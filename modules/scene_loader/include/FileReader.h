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
		std::string modelName;
		float location[3];
		float rotation[3];
		float scale[3];
	};

	virtual std::vector<FileGameObject> GetFileGameObjects(const std::string& path) const = 0;

};
