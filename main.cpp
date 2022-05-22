#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tigl.h>
#include "modules/fpscam/include/FpsCam.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>
#include <random>

using tigl::Vertex;

GLFWwindow *window;

void init();

void update();

void draw();

void addCube();

GLuint createTexture(char *textureFile);


int main() {
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW");

    int count;
    glfwGetMonitors(&count);

    window = glfwCreateWindow(854, 480, "hello world", nullptr, nullptr);
    if (count > 1) {
        glfwSetWindowMonitor(window, nullptr, 1000, -600, 854, 480, GLFW_DONT_CARE);
    }
    // get resolution of monitor


    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Could not initialize GLFW");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    tigl::init();
    init();

    while (!glfwWindowShouldClose(window)) {
        update();
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}


FpsCam *camera;

void init() {
    int value[10];
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, value);
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });
    camera = new FpsCam(window);
}


float rotation = 0.0f;

void update() {
    camera->update(window);
    rotation = (0.001f + rotation);
    if (rotation > 2 * 3.1415) {
        rotation = 0.0f;
    }

}

void draw() {
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float) viewport[2] / (float) viewport[3], 0.01f,
                                            100.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(camera->getMatrix());
    tigl::shader->enableColor(true);

    glEnable(GL_DEPTH_TEST);


    glm::mat4 cubeModelMatrix = glm::mat4(1.0f);
    cubeModelMatrix = glm::translate(cubeModelMatrix, glm::vec3(0, 0, 0));
    cubeModelMatrix = glm::rotate(cubeModelMatrix, rotation, glm::vec3(1, 0, 0));
    tigl::shader->setModelMatrix(cubeModelMatrix);
    addCube();


    cubeModelMatrix = glm::mat4(1.0f);
    cubeModelMatrix = glm::translate(cubeModelMatrix, glm::vec3(2, 0, 0));
    cubeModelMatrix = glm::rotate(cubeModelMatrix, rotation, glm::vec3(0, 1, 0));
    tigl::shader->setModelMatrix(cubeModelMatrix);
    addCube();

    cubeModelMatrix = glm::mat4(1.0f);
    cubeModelMatrix = glm::translate(cubeModelMatrix, glm::vec3(4, 0, 0));
    cubeModelMatrix = glm::rotate(cubeModelMatrix, rotation, glm::vec3(0, 0, 1));
    tigl::shader->setModelMatrix(cubeModelMatrix);
    addCube();


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


void addCube() {
    tigl::begin(GL_QUADS);
    glm::vec3 offsetVector = glm::vec3(-0.5, -0.5, -0.5); //used for anchor correction
    //front face
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 0, 0) + offsetVector, glm::vec2(1, 1), glm::vec4(1, 0, 0, 1))); //1
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 0, 0) + offsetVector, glm::vec2(0, 1), glm::vec4(1, 0, 0, 1))); //2
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 1, 0) + offsetVector, glm::vec2(0, 0), glm::vec4(1, 0, 0, 1))); //3
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 1, 0) + offsetVector, glm::vec2(1, 0), glm::vec4(1, 0, 0, 1))); //4
    //back face
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 0, 1) + offsetVector, glm::vec2(1, 1), glm::vec4(0, 1, 0, 1))); //5
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 0, 1) + offsetVector, glm::vec2(0, 1), glm::vec4(0, 1, 0, 1))); //6
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 1, 1) + offsetVector, glm::vec2(0, 0), glm::vec4(0, 1, 0, 1))); //7
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 1, 1) + offsetVector, glm::vec2(1, 0), glm::vec4(0, 1, 0, 1))); //8
    //right face
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 0, 0) + offsetVector, glm::vec2(1, 1), glm::vec4(0, 0, 1, 1))); //2
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 0, 1) + offsetVector, glm::vec2(0, 1), glm::vec4(0, 0, 1, 1))); //6
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 1, 1) + offsetVector, glm::vec2(0, 0), glm::vec4(0, 0, 1, 1))); //7
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 1, 0) + offsetVector, glm::vec2(1, 0), glm::vec4(0, 0, 1, 1))); //3
    //left face
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 0, 0) + offsetVector, glm::vec2(1, 1), glm::vec4(0, 1, 1, 1))); //1
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 0, 1) + offsetVector, glm::vec2(0, 1), glm::vec4(0, 1, 1, 1))); //5
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 1, 1) + offsetVector, glm::vec2(0, 0), glm::vec4(0, 1, 1, 1))); //8
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 1, 0) + offsetVector, glm::vec2(1, 0), glm::vec4(0, 1, 1, 1))); //4
    //bottom face
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 0, 0) + offsetVector, glm::vec2(0, 0), glm::vec4(1, 0, 1, 1))); //4
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 0, 0) + offsetVector, glm::vec2(1, 0), glm::vec4(1, 0, 1, 1))); //3
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 0, 1) + offsetVector, glm::vec2(1, 1), glm::vec4(1, 0, 1, 1))); //7
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 0, 1) + offsetVector, glm::vec2(0, 1), glm::vec4(1, 0, 1, 1))); //8
    //top face
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 1, 0) + offsetVector, glm::vec2(0, 0), glm::vec4(1, 1, 0, 1))); //4
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 1, 0) + offsetVector, glm::vec2(1, 0), glm::vec4(1, 1, 0, 1))); //3
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 1, 1) + offsetVector, glm::vec2(1, 0), glm::vec4(1, 1, 0, 1))); //7
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 1, 1) + offsetVector, glm::vec2(0, 0), glm::vec4(1, 1, 0, 1))); //8

    tigl::end();
}


GLuint createTexture(char *textureFile) {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);


    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    unsigned char data[32 * 32 * 4];
    for (unsigned char &i: data)
        i = dist(mt);
    glTexImage2D(GL_TEXTURE_2D,
                 0, //level
                 GL_RGBA, //internal format
                 32, //width
                 32, //height
                 0, //border
                 GL_RGBA, //data format
                 GL_UNSIGNED_BYTE, //data type
                 data); //data
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureId;
}





