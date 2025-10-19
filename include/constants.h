#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <random>

const double TPS = 100;
const double DT = 1 / TPS;

const double TARGET_FPS = 120.0;
const double FRAME_TIME = 1.0 / TARGET_FPS;

// Conversion factor from KM^3 S^-2 to AU^3 d^-2
const float CONVERSTION_FACTOR = 2.229e-15; 
const float AU = 1.496e11;
const float SOLAR_MASS = 1.989e30;

const float EPSILON = 1e-1;
const float PI = 3.14159265359;
const float G = 132712449941.279319 * CONVERSTION_FACTOR;

const float DISTANCE_SCALE = 1.0f / AU;
const float MASS_SCALE = 1.0f / SOLAR_MASS;

const float WIDTH = 800;
const float HEIGHT = 600;

const glm::vec2 SCREENSIZE(WIDTH, HEIGHT);
const float TOP = HEIGHT / 2;
const float BOTTOM = -HEIGHT / 2;
const float LEFT = -WIDTH / 2;
const float RIGHT = WIDTH / 2;

const float PAN_SPEED = 5e-3f;

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
