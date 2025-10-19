#include "camera.h"
#include <glm/glm.hpp>

float Camera::changeZoom(float _z) {
  this->zoom *= _z;
  return this->zoom;
}

glm::vec2 Camera::move(glm::vec2 _m) {
  this->position += _m;
  return this->position;
}

void Camera::apply() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glm::vec2 scaledSize = SCREENSIZE / zoom;

  glOrtho(position.x - scaledSize.x, position.x + scaledSize.x,
          position.y - scaledSize.y, position.y + scaledSize.y,
          -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
