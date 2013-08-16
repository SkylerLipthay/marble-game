#ifndef SKYLIB_ENGINE_H_
#define SKYLIB_ENGINE_H_

#include <skylib/state_manager.h>
#include <skylib/common/color.h>
#include <skylib/resource/resource_manager.h>

namespace skylib {

class Engine {
 public:
  void Initialize(int width, int height);
  void SetClearColor(Color color) const;
  void Clear() const;
  void Update();
  void Draw();
  void SetProjectionParallel(float bound_width, float bound_height, float near,
                             float far) const;
  int SetProjectionParallel(float max, float near, float far) const;
  void SetProjectionPerspective(float angle, float near, float far);
  void UpdateSize(int width, int height);
  StateManager& GetStateManager();
  ResourceManager& GetResourceManager();

 private:
  int width_;
  int height_;
  float angle_;
  float near_;
  float far_;
  bool perspective_;
  StateManager state_manager_;
  ResourceManager resource_manager_;
};

} // namespace skylib

#endif // SKYLIB_ENGINE_H_
