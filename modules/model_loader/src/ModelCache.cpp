//
// Created by Ewout on 16-6-2022.
//

#include "ModelCache.h"
#include <iostream>

ModelCache::DrawAbles ModelCache::getObjModel(const std::string& fileName)
{

	auto modelFound = modelCacheMap.find(fileName);
	DrawAbles drawAbles;

	if (modelFound != modelCacheMap.end())
	{
		std::cout << "getting model from cache" << fileName << std::endl;
		drawAbles = modelFound->second;
	}
	else
	{
		std::cout << "getting model from drive" << fileName << std::endl;
		auto objModel = new ObjModel(fileName);
		drawAbles = objModel->getDrawables();
		delete objModel;
		modelCacheMap.insert({fileName, drawAbles});
	}
	return drawAbles;
}
