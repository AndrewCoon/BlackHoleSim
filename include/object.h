
class Object {
public:
  vec2 position;
  vec2 velocity;
  float mass;
  float radius;
  vec3 color;

  Object(vec2 _pos, vec2 _vel, float _mass, float _r, vec3 _col) {
    this->position = _pos;
    this->velocity = _vel;
    this->mass = _mass;
    this->radius = _r;
    this->color = _col;
  }
  
  vec2 accelerate(vec2 _accel) {
    this->velocity += _accel * DT;
    return this->velocity;
  }

  vec2 updatePosition() {
    this->position += velocity * DT;
    return this->position;
  }

  void step() {
    this->updatePosition();
    this->checkCollisions();
  }

  void checkCollisions() {
    if (this->position.y < -TOP || this->position.y > TOP) {
      this->velocity.y *= -0.95;
      this->position.y = clamp(this->position.y, -TOP, TOP);
    }

    if (this->position.x < LEFT || this->position.x > -LEFT) {
      this->velocity.x *= -0.95;
      this->position.x = clamp(this->position.x, LEFT, -LEFT);
    }
  }

  void draw(int _resolution) {
    glColor3f(this->color.x, this->color.y, this->color.z);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(this->position.x, this->position.y);

    for (int i = 0; i <= _resolution; i++) {
      float angle = 2.0f * PI * (static_cast<float>(i) / _resolution);
      float x = this->position.x + cos(angle) * this->radius;
      float y = this->position.y + sin(angle) * this->radius;
      glVertex2d(x, y);
    }
    glEnd();
  }
};
