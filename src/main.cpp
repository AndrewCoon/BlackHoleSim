#include "constants.h"
#include "object.h"
#include "engine.h"

using namespace glm;
using namespace std;

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



