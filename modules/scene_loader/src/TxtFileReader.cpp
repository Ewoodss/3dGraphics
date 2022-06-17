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
		fileGameObject.ModelName = line;

		getline(pFile, line, ' ');
		if (line[0] != 'L') continue;
		getline(pFile, line, ',');
		fileGameObject.Location[0] = strtof(line.c_str(), nullptr);
		getline(pFile, line, ',');
		fileGameObject.Location[1] = strtof(line.c_str(), nullptr);
		getline(pFile, line);
		fileGameObject.Location[2] = strtof(line.c_str(), nullptr);

		getline(pFile, line, ' ');
		if (line[0] != 'R') continue;
		getline(pFile, line, ',');
		fileGameObject.Rotation[0] = strtof(line.c_str(), nullptr);
		getline(pFile, line, ',');
		fileGameObject.Rotation[1] = strtof(line.c_str(), nullptr);
		getline(pFile, line);
		fileGameObject.Rotation[2] = strtof(line.c_str(), nullptr);

		getline(pFile, line, ' ');
		if (line[0] != 'S') continue;
		getline(pFile, line, ',');
		fileGameObject.Scale[0] = strtof(line.c_str(), nullptr);
		getline(pFile, line, ',');
		fileGameObject.Scale[1] = strtof(line.c_str(), nullptr);
		getline(pFile, line);
		fileGameObject.Scale[2] = strtof(line.c_str(), nullptr);

		fileGameObjects.push_back(fileGameObject);
	}

	pFile.close();
	return fileGameObjects;
}