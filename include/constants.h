#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <random>

const double TARGET_FPS = 120.0;
const double FRAME_TIME = 1.0 / TARGET_FPS;

const float EPSILON = 10;
const float PI = 3.14159265359;
const float G = 1.0f;
const float DISTANCE_MULT = 1.0f;
// const float G = 6.6743e-11;
const float c = 299792458.0;
const float DT = 1e-2;

const int RES = 100;
const float WIDTH = 800;
const float HEIGHT = 600;
const glm::vec2 SCREENSIZE(WIDTH, HEIGHT);
const float TOP = HEIGHT / 2;
const float BOTTOM = -HEIGHT / 2;
const float LEFT = -WIDTH / 2;
const float RIGHT = WIDTH / 2;

static std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

static float randf(float a, float b) {
    std::uniform_real_distribution<float> d(a, b);
    return d(rng());
}

static glm::vec2 randVec2(float xmin, float xmax, float ymin, float ymax) {
    return glm::vec2(randf(xmin, xmax), randf(ymin, ymax));
}

static glm::vec3 randColor() {
    return glm::vec3(randf(0.0f,1.0f), randf(0.0f,1.0f), randf(0.0f,1.0f));
}
