//
// Created by Ewout on 17-6-2022.
//

#pragma once

#include "FileReader.h"
class TxtFileReader : public FileReader
{

public:
	std::vector<FileGameObject> GetFileGameObjects(const std::string& path) const override;
};
