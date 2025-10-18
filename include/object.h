#pragma once
#include "constants.h"
#include <glm/glm.hpp>

class Object {
public:
    glm::vec2 position;
    glm::vec2 velocity;
    float mass;
    float radius;
    glm::vec3 color;

    Object(glm::vec2 _pos, glm::vec2 _vel, float _mass, float _r, glm::vec3 _col);

    glm::vec2 accelerate(glm::vec2 _accel);
    glm::vec2 updatePosition();
    void step();
    void checkCollisions();
    void draw(int _resolution);
};
