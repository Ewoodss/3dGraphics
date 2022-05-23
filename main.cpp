#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tigl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>
#include <random>


#include "FpsCam.h"
#include "ObjModel.h"


using tigl::Vertex;

GLFWwindow *window;
ObjModel *model;

void init();

void update();

void draw();

void addCube();

GLuint createTexture(const char *textureFile);

GLuint loadTexture(const char *textureFile);

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
GLuint texture;

void init() {
    int value[10];
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, value);
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });
    camera = new FpsCam(window);


    //todo this is stupid should be done outside of loop
    //texture = loadTexture(R"(..\resource\textures\leather.png)");
    model = new ObjModel("../resource/models/car/honda_jazz.obj");
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
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    //glBindTexture(GL_TEXTURE_2D, texture);
    //tigl::shader->enableTexture(true);
    glEnable(GL_DEPTH_TEST);

    glPointSize(10.0f);
    model->draw();

    //tigl::shader->setModelMatrix(glm::mat4(1.0f));

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
    tigl::addVertex(Vertex::PTC(glm::vec3(1, 1, 1) + offsetVector, glm::vec2(1, 1), glm::vec4(1, 1, 0, 1))); //7
    tigl::addVertex(Vertex::PTC(glm::vec3(0, 1, 1) + offsetVector, glm::vec2(0, 1), glm::vec4(1, 1, 0, 1))); //8

    tigl::end();
}


GLuint createTexture(const char *textureFile) {

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

//GLuint loadTexture(const char *textureFile) {
//    int width, height, bpp;
//    auto *imgData = stbi_load(textureFile, &width, &height, &bpp, 4);
//
//    GLuint textureId = 0;
//    glGenTextures(1, &textureId);
//    glBindTexture(GL_TEXTURE_2D, textureId);
//
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
//    stbi_image_free(imgData);
//
//    return textureId;
//}




