#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace glm;
using namespace std;

int main() {
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}


Engine() {
  if(!glfwInit()) {
    cerr << "glfw failed to initialize\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "Gravity Sim", NULL, NULL);
  if(!window) {
    cerr << "Window failed to create\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);


  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD\n";
      return -1;
  }
}
