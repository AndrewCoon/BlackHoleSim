#include "object.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace glm;
using namespace std;

Object::Object(vec2 _pos, vec2 _vel, float _mass, float _r, vec3 _col)
    : position(_pos), velocity(_vel), mass(_mass), radius(_r), color(_col) {}

vec2 Object::accelerate(vec2 _accel) {
    velocity += _accel * DT;
    return velocity;
}

vec2 Object::updatePosition() {
    position += velocity * DT;
    return position;
}

void Object::step() {
    updatePosition();
    // checkCollisions();
}

void Object::checkCollisions() {
    if (position.y < -TOP || position.y > TOP) {
        velocity.y *= -0.95;
        position.y = clamp(position.y, -TOP, TOP);
    }

    if (position.x < LEFT || position.x > -LEFT) {
        velocity.x *= -0.95;
        position.x = clamp(position.x, LEFT, -LEFT);
    }
}

void Object::draw(int _resolution) {
    glColor3f(color.x, color.y, color.z);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(position.x, position.y);

    for (int i = 0; i <= _resolution; i++) {
        float angle = 2.0f * 3.14159265359f * (float)i / _resolution;
        float x = position.x + cos(angle) * radius;
        float y = position.y + sin(angle) * radius;
        glVertex2d(x, y);
    }
    glEnd();
}
