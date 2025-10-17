#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
using namespace glm;
using namespace std;

#define PI 3.14159265359

const float DT = 0.1;
const int RES = 100;
const int WIDTH = 800;
const int HEIGHT = 600;
const int TOP = HEIGHT / 2;
const int LEFT = -WIDTH / 2;

class Object {
public:
  vec2 position;
  vec2 velocity;
  vec2 acceleration;
  float radius;
  vec3 color;

  Object(vec2 _pos, vec2 _vel, vec2 _accel, float _r, vec3 _col) {
    this->position = _pos;
    this->velocity = _vel;
    this->acceleration = _accel;
    this->radius = _r;
    this->color = _col;
  }

  vec2 getAcceleration() {
    return this-> acceleration;
  }

  vec2 accelerate() {
    this->velocity += acceleration * DT;
    return this->velocity;
  }

  vec2 updatePosition() {
    this->position += velocity * DT;
    return this->position;
  }

  void step() {
    this->accelerate();
    this->updatePosition();
    this->checkCollisions();
  }

  void checkCollisions() {
    if (this->position.y < -TOP || this->position.y > TOP) {
      this->velocity.y *= -0.95;
    }

    if (this->position.x < LEFT || this->position.x > -LEFT) {
      this->velocity.x *= -0.95;
    }
  }

  void draw(int _resolution) {
    glColor3f(this->color.x, this->color.y, this->color.z);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(this->position.x, this->position.y);

    for (int i = 0; i <= _resolution; i++) {
      float angle = 2.0f * PI * (static_cast<float>(i) / _resolution);
      float x = this->position.x + cos(angle) * this->radius;
      float y = this->position.y + sin(angle) * this->radius;
      glVertex2d(x, y);
    }
    glEnd();
  }
};

class Engine {
public:
  GLFWwindow* window;
  vector<Object> objects;

  Engine() {
    this->window=StartGLFW();
  }

  vector<Object> setObjects(vector<Object> _n) {
    this->objects = _n;
    return this->objects;
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


    glMatrixMode(GL_PROJECTION);
    double left = -WIDTH / 2.0;
    double right = WIDTH / 2.0;
    double bottom = -HEIGHT / 2.0;
    double top = HEIGHT / 2.0;
    glOrtho(left, right, bottom, top, -1.0, 1.0);

    return window;
  }
  void run() {
    processInput(this->window);
    render();
  }
  

  void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    for(auto& obj:this->objects) {
      obj.step();
      obj.draw(RES);
    }
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

int main() {
  Engine engine;

  vector<Object> objs = {
    Object(vec2(-100, -100), vec2(10, 0), vec2(0, -9.8), 25.0f, vec3(190.0f / 255.0f, 0.0f, 0.0f)),
    Object(vec2(100, 100), vec2(20, 0), vec2(0, -9.8), 25.0f, vec3(0.0f, 106.0f, 200.0f))
  };

  engine.setObjects(objs);

  while (!glfwWindowShouldClose(engine.window)) {
    engine.run();

    glfwSwapBuffers(engine.window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}



