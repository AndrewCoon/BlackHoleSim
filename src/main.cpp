#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
using namespace glm;
using namespace std;

#define PI 3.14159265359

const int WIDTH = 800;
const int HEIGHT = 600;

class Engine {
public:
  GLFWwindow* window;

  Engine() {
    this->window=StartGLFW();
  }
  GLFWwindow* StartGLFW() {
    if(!glfwInit()) {
      cerr << "glfw failed to initialize\n";
      return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ray Tracer", NULL, NULL);
    if (!window) {
        cerr << "Failed to create GLFW window\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      cerr << "Failed to initialize GLAD\n";
      glfwDestroyWindow(window);
      glfwTerminate();
      return nullptr;
    }
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    return window;
  }
  void run() {
    processInput(this->window);
    render();
  }
  
  void drawCircle(vec2 _center, int _radius, int _resolution) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(_center.x, _center.y);

    for (int i = 0; i <= _resolution; i++) {
      float angle = 2.0f * PI * (static_cast<float>(i) / _resolution);
      float x = _center.x + cos(angle) * _radius;
      float y = _center.y + sin(angle) * _radius;
      glVertex2d(x, y);
    }
    glEnd();
  }

  void render() {

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    double left = -WIDTH / 2.0;
    double right = WIDTH / 2.0;
    double bottom = -HEIGHT / 2.0;
    double top = HEIGHT / 2.0;

    glOrtho(left, right, bottom, top, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    vec2 test(0.0f,0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    drawCircle(test, 1, 100);
  }
private:
  void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
  }
  static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
     glViewport(0, 0, width, height);
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



