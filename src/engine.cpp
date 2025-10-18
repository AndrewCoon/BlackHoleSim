#include "engine.h"
#include "constants.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;


Engine::Engine() {
  this->window = StartGLFW();
  paused = true;
}

vector<Object> Engine::setObjects(vector<Object> _n) {
    this->objects = _n;
    return this->objects;
}

GLFWwindow* Engine::StartGLFW() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW\n";
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Gravity Simulation", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return nullptr;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glOrtho(LEFT, RIGHT, BOTTOM, TOP, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return window;
}

void Engine::run() {
  processInput(window);

  if (!paused) {
    simulate();
  }

  render();
}

void Engine::simulate() {
    for (auto& obj : objects) {
        for (auto& obj2 : objects) {
            if (&obj == &obj2) continue;

            vec2 distance = obj2.position - obj.position;
            float r = length(distance);
            if (r < 1.0f) r = 1.0f;
            r *= 1000;
      
            vec2 dir = normalize(distance);

            if (r < obj.radius + obj2.radius) {
              obj.velocity *= -0.2f;
            } 
            vec2 force = dir * (G * obj.mass * obj2.mass) / (r * r);
            vec2 deltaAccel = force / obj.mass;
            obj.accelerate(deltaAccel);
        }
    }
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& obj : objects) {
      if (!paused) obj.step();
      obj.draw(RES);
    }
}

static bool spaceWasPressed = false;
void Engine::processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    if (!spaceWasPressed) {
      paused = !paused;
      spaceWasPressed = true;
    }
  } else {
    spaceWasPressed = false;
  }
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
