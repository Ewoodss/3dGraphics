#include <tigl.h>
//This comment is here so that tigl stays at the top even on code reformatting. tigl needs to load first then glfw otherwise glad gets included twice
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "FileReaderFactory.h"
#include "GameTimer.h"
#include "Scene.h"
#include "SceneLoader.h"
#include "components/Camera.h"
#include "components/Mesh.h"
#include "components/Transform.h"
#include "components/scripts/TankScript.h"

void Init();

void Update();

void Draw();

void WorldInit();

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		throw std::runtime_error("Could not initialize GLFW");

	int count;
	glfwGetMonitors(&count);

	window = glfwCreateWindow(1280, 720, "hello world", nullptr, nullptr);
	if (count > 1)
	{
		glfwSetWindowMonitor(window, nullptr, 500, -800, 1280, 720, 240);
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, 0, 0, 1280, 720, 240);
	}
	// get resolution of monitor
	glfwSwapInterval(1);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Could not initialize GLFW");
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	tigl::init();
	Init();
	WorldInit();

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	while (!glfwWindowShouldClose(window))
	{
		Update();
		Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void Init()
{
	int value[10];
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, value);
}

std::shared_ptr<Scene> scene;

void GeneratePlayerTank()
{
	auto tankGameObject = std::make_shared<GameObject>();
	auto transform = tankGameObject->AddComponent<Transform>(glm::vec3(0, 0, 0),
	                                                         glm::radians(glm::vec3(0.0f, 12.0f, 0.0f)),
	                                                         glm::vec3(1.0f, 1.0f, 1.0f));
	tankGameObject->AddComponent<Mesh>(transform, "../resource/models/tanks/tank2.obj");
	tankGameObject->AddComponent<Camera>(scene, transform);
	tankGameObject->AddComponent<TankScript>(scene, transform);
	scene->AddGameObject(tankGameObject);
}

void LoadGround()
{
	auto groundObject = std::make_shared<GameObject>();
	auto transform = groundObject->AddComponent<Transform>(glm::vec3(0, -1.0f, 0));
	groundObject->AddComponent<Mesh>(transform, "../resource/models/ground/ground.obj");
	scene->AddGameObject(groundObject);
}

void WorldInit()
{
	scene = std::make_shared<Scene>();

	SceneLoader::LoadScene(scene, "../resource/scenes/scene.json");

	GeneratePlayerTank();
	LoadGround();
}

//float rotation = 0.0f;
void Update()
{
	GameTimer::Update(glfwGetTime());
	scene->Update();
}

void Draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)viewport[2] / (float)viewport[3], 0.01f,
	                                        100.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(scene->GetViewMatrix());
	tigl::shader->enableColor(true);
	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::shader->enableFog(true);
	tigl::shader->setFogColor(glm::vec3(0.3f, 0.4f, 0.6f));
	tigl::shader->setFogExp2(0.02f);
	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::vec3(1, 2, 3));

	tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
	tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
	tigl::shader->setShinyness(32.0f);

	//glBindTexture(GL_TEXTURE_2D, texture);
	//tigl::shader->enableTexture(true);
	glEnable(GL_DEPTH_TEST);
	glPointSize(10.0f);

	scene->Draw();

	//tigl::shader->setModelMatrix(glm::mat4(1.0f));
	//	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	//	tigl::begin(GL_TRIANGLES);
	//
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-10, -1, 10), glm::vec4(1, 1, 1, 1)));
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));
	//
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(10, -1, -10), glm::vec4(1, 1, 1, 1)));
	//	tigl::addVertex(tigl::Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));
	//
	//	tigl::end();
}

void KeyCallback(GLFWwindow*, int key, int, int action, int)
{
	scene->GetInputSystem().TriggerKeyFunction(key, action);
}

void FramebufferSizeCallback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
	Draw();
}
