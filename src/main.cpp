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
    float massMin = 0, massMax = 4;
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

vec2 circularOrbitVelocity(const vec2& centerPos, float massCenter, const vec2& objPos) {
    vec2 rVec = objPos - centerPos;
    float r = length(rVec);
    float speed = sqrt(G * massCenter / r); // G is already in sim units
    return vec2(-rVec.y, rVec.x) * (speed / r); // perpendicular velocity
}

vector<Object> generateSolarSystem() {
    vector<Object> bodies;

    // Sun
    float sunMass = 1.0f; // 1 solar mass in sim units
    float sunRadius = 0.05f; // scaled for rendering
    bodies.emplace_back(vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), sunMass, sunRadius, vec3(1.0f, 1.0f, 0.0f));

    // Planets
    struct PlanetInfo { float distanceMeters; float massKg; float radius; vec3 color; };
    vector<PlanetInfo> planets = {
        { 0.387f * AU, 3.3e23f, 0.01f, vec3(0.5f,0.5f,0.5f) },   // Mercury
        { 0.723f * AU, 4.87e24f, 0.015f, vec3(1.0f,0.7f,0.0f) }, // Venus
        { 1.0f * AU,   5.97e24f, 0.02f, vec3(0.0f,0.0f,1.0f) },  // Earth
        { 1.524f * AU, 0.642e24f, 0.015f, vec3(1.0f,0.0f,0.0f) } // Mars
    };

    for (auto& p : planets) {
        // Scale distance and mass
        vec2 pos = vec2(p.distanceMeters * DISTANCE_SCALE, 0.0f);
        float massSim = p.massKg * MASS_SCALE;

        // Circular orbit velocity (scaled)
        vec2 vel = circularOrbitVelocity(vec2(0.0f,0.0f), sunMass, pos);

        bodies.emplace_back(pos, vel, massSim, p.radius, p.color);
    }

    return bodies;
}

int main() {
  Engine engine;

  vector<Object> objs = {
    Object(vec2(0, 0), vec2(0, 0), 7.35e2, 15.0f, vec3(190.0f / 255.0f, 0.0f, 0.0f)),
    Object(vec2(300, 0), vec2(0, 10), 7.35e-4, 15.0f, vec3(0.0f, 106.0f / 255.0f, 200.0f / 255.0f))
  };

  // engine.setObjects(objs); 
  // engine.setObjects(randomField(200));
  engine.setObjects(generateCircularOrbit(200, vec2(0.0f, 0.0f), 1e8, 150, 1000));
  // engine.setObjects(generateSolarSystem());

  double accum = 0.0;
  double lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(engine.window)) {
    double currentTime = glfwGetTime();
    double elapsed = currentTime - lastTime;
    lastTime = currentTime;

    accum += elapsed;

    while (accum >= DT) {
      engine.run();
      accum -= DT;
    }

    engine.render();
    glfwSwapBuffers(engine.window);
    glfwPollEvents();

    double frameTime = glfwGetTime() - currentTime;
    if (frameTime < FRAME_TIME)
      this_thread::sleep_for(chrono::duration<double>(FRAME_TIME - frameTime));
  }

  glfwTerminate();
  return 0;
}


