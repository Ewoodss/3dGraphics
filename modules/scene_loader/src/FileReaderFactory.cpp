//
// Created by Ewout on 17-6-2022.
//

#include "FileReaderFactory.h"
#include "JsonFileReader.h"
#include "TxtFileReader.h"
#include <stdexcept>

std::shared_ptr<FileReader> FileReaderFactory::GetFileReader(FileReaderFactory::FileType type)
{
	if (type == FileType::json)
	{
		return std::make_shared<JsonFileReader>();
	}

	if (type == FileType::txt)
	{
		return std::make_shared<TxtFileReader>();
	}

	throw std::runtime_error("file type not supported");
}
