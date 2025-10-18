#include "constants.h"
#include "object.h"

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
