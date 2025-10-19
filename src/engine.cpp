#include "engine.h"
#include "constants.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;


Engine::Engine() : camera() {
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

  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

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
  camera.apply();

  for (auto& obj : objects) {
    if (!paused) obj.step();
    drawObject(obj);
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


  // Zoom
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) camera.changeZoom(1.02f);
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) camera.changeZoom(0.98f);

  // Pan
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.move(glm::vec2(0.0f, 10.0f / camera.zoom));
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.move(glm::vec2(0.0f, -10.0f / camera.zoom));
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.move(glm::vec2(-10.0f / camera.zoom, 0.0f ));
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.move(glm::vec2(10.0f / camera.zoom, 0.0f ));
}

// When transitioned to use z coordinates keep this function, but have it call the function that uses a vec3 with a z coord of 0
void Engine::drawCircle(vec2 position, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(position.x, position.y);
    for (int i = 0; i <= RES; i++) {
        float angle = 2.0f * PI * (float)i / RES;
        float x = position.x + cos(angle) * radius;
        float y = position.y + sin(angle) * radius;
        glVertex2d(x, y);
    }
    glEnd();
}

void Engine::drawObject(const Object& obj) {
  glColor3f(obj.color.x, obj.color.y, obj.color.z);
  glPointSize(obj.radius * camera.zoom);

  glBegin(GL_POINTS);
  glVertex2f(obj.position.x, obj.position.y);
  glEnd();
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

