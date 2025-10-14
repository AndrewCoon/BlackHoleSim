#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
using namespace glm;
using namespace std;

struct Engine {
public:
  GLFWwindow* window;

  int WIDTH = 800;
  int HEIGHT = 600;

  Engine() {
    this->window=StartGLFW();
  }
  GLFWwindow* StartGLFW() {
    if(!glfwInit()) {
      cerr << "glfw failed to initialize\n";
      return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ray Tracer", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  }

  void run() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    double left = -WIDTH;
    double right = WIDTH;
    double bottom = -HEIGHT;
    double top = HEIGHT;

    glOrtho(left, right, bottom, top, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
};
Engine engine;

int main() {
  while (!glfwWindowShouldClose(engine.window)) {
    engine.run();

    glfwSwapBuffers(engine.window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}



