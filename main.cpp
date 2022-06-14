#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tigl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>

#include "FpsCam.h"
#include "components/Transform.h"
#include "Scene.h"
#include "components/Mesh.h"
#include "components/Camera.h"


using tigl::Vertex;

GLFWwindow *window;


void init();

void update();

void draw();

void worldInit();


int main()
{
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW");

    int count;
    glfwGetMonitors(&count);

    window = glfwCreateWindow(854, 480, "hello world", nullptr, nullptr);
//    if (count > 1)
//    {
//        glfwSetWindowMonitor(window, nullptr, 1000, -600, 854, 480, GLFW_DONT_CARE);
//    }
    // get resolution of monitor


    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Could not initialize GLFW");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    tigl::init();
    init();
    worldInit();

    while (!glfwWindowShouldClose(window))
    {
        update();
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}


GLuint texture;

std::shared_ptr<Scene> scene;

void init()
{
    int value[10];
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, value);

}


void worldInit()
{
    scene = std::make_shared<Scene>();

    auto tankGameObject = std::make_shared<GameObject>();
    auto transform = tankGameObject->AddComponent<Transform>(glm::vec3(5, 0, 0), glm::radians(glm::vec3(0, 0, 0)),
                                                             glm::vec3(0.1f, 0.1f, 0.1f));
    tankGameObject->AddComponent<Mesh>(transform, "../resource/models/tanks/tank2.obj");
    tankGameObject->AddComponent<Camera>(scene, transform);


    scene->AddGameObject(tankGameObject);
}


//float rotation = 0.0f;

void update()
{
    scene->Update();
}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float) viewport[2] / (float) viewport[3], 0.01f,
                                            100.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(scene->getViewMatrix());
    tigl::shader->enableColor(true);
    tigl::shader->setModelMatrix(glm::mat4(1.0f));
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
    tigl::shader->setModelMatrix(glm::mat4(1.0f));
    tigl::begin(GL_TRIANGLES);

    tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, 10), glm::vec4(1, 1, 1, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));

    tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(10, -1, -10), glm::vec4(1, 1, 1, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));

    tigl::end();
}