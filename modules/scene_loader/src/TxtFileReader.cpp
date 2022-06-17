//
// Created by Ewout on 17-6-2022.
//

#include "TxtFileReader.h"
#include <fstream>
#include <iostream>
std::vector<FileReader::FileGameObject> TxtFileReader::GetFileGameObjects(const std::string& path) const
{
	std::vector<FileReader::FileGameObject> fileGameObjects;

	std::ifstream pFile(path.c_str());

	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << path << std::endl;
		return fileGameObjects;
	}

	while (!pFile.eof())
	{
		FileReader::FileGameObject fileGameObject;

		std::string line;
		getline(pFile, line, ' ');
		if (line[0] != 'F') continue;
		getline(pFile, line);
		fileGameObject.modelName = line;

		getline(pFile, line, ' ');
		if (line[0] != 'L') continue;
		getline(pFile, line, ',');
		fileGameObject.location[0] = strtof(line.c_str(), nullptr);
		getline(pFile, line, ',');
		fileGameObject.location[1] = strtof(line.c_str(), nullptr);
		getline(pFile, line);
		fileGameObject.location[2] = strtof(line.c_str(), nullptr);

		getline(pFile, line, ' ');
		if (line[0] != 'R') continue;
		getline(pFile, line, ',');
		fileGameObject.rotation[0] = strtof(line.c_str(), nullptr);
		getline(pFile, line, ',');
		fileGameObject.rotation[1] = strtof(line.c_str(), nullptr);
		getline(pFile, line);
		fileGameObject.rotation[2] = strtof(line.c_str(), nullptr);

		getline(pFile, line, ' ');
		if (line[0] != 'S') continue;
		getline(pFile, line, ',');
		fileGameObject.scale[0] = strtof(line.c_str(), nullptr);
		getline(pFile, line, ',');
		fileGameObject.scale[1] = strtof(line.c_str(), nullptr);
		getline(pFile, line);
		fileGameObject.scale[2] = strtof(line.c_str(), nullptr);

		fileGameObjects.push_back(fileGameObject);
	}

	pFile.close();
	return fileGameObjects;
}