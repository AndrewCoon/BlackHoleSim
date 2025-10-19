#include <thread>
#include <random>
#include <chrono>
#include "constants.h"
#include "object.h"
#include "engine.h"

using namespace glm;
using namespace std;

std::vector<Object> randomField(int N) {
    std::vector<Object> v;
    v.reserve(N);
    float massMin = 1e2, massMax = 1e3f;
    float speed = 20.0f;
    float radiusMin = 2.0f, radiusMax = 6.0f;

    for (int i = 0; i < N; ++i) {
        glm::vec2 pos = randVec2(-WIDTH/2.0f, WIDTH/2.0f, -HEIGHT/2.0f, HEIGHT/2.0f);
        glm::vec2 vel = randVec2(-speed, speed, -speed, speed);
        float mass = randf(massMin, massMax);
        float radius = randf(radiusMin, radiusMax);
        glm::vec3 color = randColor();
        v.emplace_back(pos, vel, mass, radius, color);
    }
    return v;
}

static vector<Object> generateCircularOrbit(int N, vec2 center, float centralMass, float minRadius, float maxRadius) {
    vector<Object> objs;
    objs.emplace_back(Object(center, vec2(0,0), centralMass, 20, vec3(1,1,0)));
    for (int i = 0; i < N; i++) {
        float angle = randf(0.0f, 2.0f * PI);
        float dist = randf(minRadius, maxRadius);
        vec2 pos = center + vec2(cos(angle), sin(angle)) * dist;

        // Perpendicular velocity for circular orbit
        float speed = sqrt(G * centralMass / dist);
        vec2 vel = vec2(-sin(angle), cos(angle)) * speed;

        float mass = randf(1e3f, 1e5f);
        float radius = randf(8.0f, 12.0f);
        vec3 color = randColor();

        objs.emplace_back(Object(pos, vel, mass, radius, color));
    }
    return objs;
}

int main() {
  Engine engine;

  vector<Object> objs = {
    Object(vec2(0, 0), vec2(0, 0), 7.35e24, 15.0f, vec3(190.0f / 255.0f, 0.0f, 0.0f)),
    Object(vec2(300, 0), vec2(0, 1000), 7.35e22, 15.0f, vec3(0.0f, 106.0f / 255.0f, 200.0f / 255.0f))
  };

  engine.setObjects(generateCircularOrbit(200, vec2(0.0f, 0.0f), 1e8, 150, 1000));

  double lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(engine.window)) {
    double currentTime = glfwGetTime();
    double elapsed = currentTime - lastTime;

    if (elapsed >= FRAME_TIME) {
      lastTime = currentTime;
      engine.run();

      glfwSwapBuffers(engine.window);
      glfwPollEvents();
    } else {
      this_thread::sleep_for(chrono::duration<double>(FRAME_TIME - elapsed));
    }
  }

  glfwTerminate();
  return 0;
}


