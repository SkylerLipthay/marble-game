#include <skylib/engine.h>
#include <GL/gl.h>
#include <cmath>

namespace skylib {

void Engine::Initialize(int width, int height) {
  width_ = width;
  height_ = height;
  perspective_ = false;

  glViewport(0, 0, width, height);

  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_TEXTURE_2D);

  // transparency for sprites
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}

void Engine::SetClearColor(Color color) const {
  glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), 1.0f);
}

void Engine::Clear() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Update() {
  state_manager_.Update();
}

void Engine::Draw() {
  state_manager_.Draw();
}

void Engine::SetProjectionParallel(float bound_width, float bound_height,
                                   float near, float far) const {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, bound_width, 0.0f, bound_height, near, far);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int Engine::SetProjectionParallel(float max, float near, float far) const {
  float aspect = static_cast<float>(height_) / static_cast<float>(width_);
  SetProjectionParallel(max, max * aspect, near, far);

  return max * aspect;
}

void Engine::SetProjectionPerspective(float angle, float near,
                                      float far) {
  perspective_ = true;
  angle_ = angle;
  near_ = near;
  far_ = far;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspect = static_cast<float>(width_) / static_cast<float>(height_);

  float top = std::tan(angle * 0.5f) * near;
  float bottom = -top;
  float left = aspect * bottom;
  float right = aspect * top;

  glFrustum(left, right, bottom, top, near, far);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Engine::UpdateSize(int width, int height) {
  width_ = width;
  height_ = height;

  if (perspective_) {
    SetProjectionPerspective(angle_, near_, far_);
  }

  glViewport(0, 0, width_, height_);
}

StateManager& Engine::GetStateManager() {
  return state_manager_;
}

ResourceManager& Engine::GetResourceManager() {
  return resource_manager_;
}

} // namespace skylib
