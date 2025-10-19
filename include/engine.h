#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "object.h"
#include "camera.h"

class Engine {
public:
    GLFWwindow* window;
    std::vector<Object> objects;
    bool paused;
    Camera camera;
    Engine();
    std::vector<Object> setObjects(std::vector<Object> _n);
    void run();

private:

    GLFWwindow* StartGLFW();
    void processInput(GLFWwindow* window);
    void drawCircle(glm::vec2 position, float radius);
    void drawObject(const Object& obj);
    void simulate();
    void render();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
