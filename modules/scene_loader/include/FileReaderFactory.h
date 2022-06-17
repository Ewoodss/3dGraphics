//
// Created by Ewout on 17-6-2022.
//
#pragma once

#include "FileReader.h"
#include <memory>
class FileReaderFactory
{
public:
	enum FileType
	{
		json,
		txt,
		none,
	};

	static std::shared_ptr<FileReader> GetFileReader(FileType type);
};
