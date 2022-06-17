//
// Created by Ewout on 16-6-2022.
//

#pragma once

#include "ObjModel.h"
#include <unordered_map>

class ModelCache
{
public:
	typedef std::vector<ObjModel::Drawable> DrawAbles;

private:
	inline static std::unordered_map<std::string, DrawAbles> modelCacheMap;

public:
	static DrawAbles GetObjModel(const std::string& fileName);
};