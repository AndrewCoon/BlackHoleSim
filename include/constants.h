#pragma once

#include <glm/glm.hpp>
#include <iostream>

const double TARGET_FPS = 120.0;
const double FRAME_TIME = 1.0 / TARGET_FPS;

const float PI = 3.14159265359;
const float G = 6.6743e-11;
const float c = 299792458.0;
const float DT = 1e-3;

const int RES = 100;
const float WIDTH = 800;
const float HEIGHT = 600;
const glm::vec2 SCREENSIZE(WIDTH, HEIGHT);
const float TOP = HEIGHT / 2;
const float BOTTOM = -HEIGHT / 2;
const float LEFT = -WIDTH / 2;
const float RIGHT = WIDTH / 2;
