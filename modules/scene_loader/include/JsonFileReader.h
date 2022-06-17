//
// Created by Ewout on 17-6-2022.
//

#pragma once

#include "FileReader.h"

class JsonFileReader : public FileReader
{
public:
	[[nodiscard]] std::vector<FileGameObject> GetFileGameObjects(const std::string& path) const override;
};