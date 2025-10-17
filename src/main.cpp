#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
using namespace glm;
using namespace std;

const float PI = 3.14159265359;
const float G = 6.6743e-11;
const float c = 299792458.0;
const float DT = 1e-3;
const int RES = 100;
const float WIDTH = 800;
const float HEIGHT = 600;
const float TOP = HEIGHT / 2;
const float LEFT = -WIDTH / 2;

class Object {
public:
  vec2 position;
  vec2 velocity;
  float mass;
  float radius;
  vec3 color;

  Object(vec2 _pos, vec2 _vel, float _mass, float _r, vec3 _col) {
    this->position = _pos;
    this->velocity = _vel;
    this->mass = _mass;
    this->radius = _r;
    this->color = _col;
  }
  
  vec2 accelerate(vec2 _accel) {
    this->velocity += _accel * DT;
    return this->velocity;
  }

  vec2 updatePosition() {
    this->position += velocity * DT;
    return this->position;
  }

  void step() {
    this->updatePosition();
    this->checkCollisions();
  }

  void checkCollisions() {
    if (this->position.y < -TOP || this->position.y > TOP) {
      this->velocity.y *= -0.95;
      this->position.y = clamp(this->position.y, -TOP, TOP);
    }

    if (this->position.x < LEFT || this->position.x > -LEFT) {
      this->velocity.x *= -0.95;
      this->position.x = clamp(this->position.x, LEFT, -LEFT);
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
    simulate();
    render();
  }
  
  void simulate() {
    for(auto& obj:this->objects) {
      for(auto& obj2:this->objects) {
        if (&obj == &obj2) continue;

        vec2 distance = obj2.position - obj.position;
        distance *= 1000;
        
        if (length(distance) > 0.4) {
          vec2 force = (distance / length(distance)) * (G * obj.mass * obj2.mass) / static_cast<float>(pow(length(distance),2));
          vec2 deltaAccel = force / obj.mass;

          obj.accelerate(deltaAccel);
        }

        if (length(distance) / 1000 < obj.radius + obj2.radius) {
          // obj.velocity *= -0.2f;
        }
      }
    }
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
    Object(vec2(0, 0), vec2(0, 0), 7.35e24,15.0f, vec3(190.0f / 255.0f, 0.0f, 0.0f)),
    Object(vec2(300, 0), vec2(0, 1000), 7.35e22, 15.0f, vec3(0.0f, 106.0f / 255.0f, 200.0f / 255.0f))
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



