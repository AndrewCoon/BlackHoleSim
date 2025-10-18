#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "object.h"

class Engine {
public:
    GLFWwindow* window;
    std::vector<Object> objects;

    Engine();
    std::vector<Object> setObjects(std::vector<Object> _n);
    void run();

private:
    bool paused;
  
    GLFWwindow* StartGLFW();
    void processInput(GLFWwindow* window);
    void simulate();
    void render();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
