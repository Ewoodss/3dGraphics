//
// Created by Ewout on 17-6-2022.
//

#pragma once

#include "FileReader.h"
#include "Scene.h"

class SceneLoader
{

public:
	static void loadScene(const std::shared_ptr<Scene>& scene, const std::string& filename);
};