#pragma once
#include <glm/glm.hpp>
#include "constants.h"
#include <glad/glad.h>

class Camera {
public:
  glm::vec2 position;
  float zoom;

  Camera(glm::vec2 _pos = glm::vec2(0.0f, 0.0f), float _zoom = 1.0f) 
   : position(_pos), zoom(_zoom) {}
  
  glm::vec2 worldToScreen(const glm::vec2& worldPos) const {
    glm::vec2 screenPos = (worldPos - position) * zoom;
    screenPos += SCREENSIZE / 2.0f;
    return screenPos;
  }

  glm::vec2 screenToWorld(const glm::vec2& screenPos) const {
    glm::vec2 worldPos = (screenPos - SCREENSIZE / 2.0f) / zoom;
    worldPos += position;
    return worldPos;
  }

  float changeZoom(float _z);
  glm::vec2 move(glm::vec2 _m);
  void apply();
};
