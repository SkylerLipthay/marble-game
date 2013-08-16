#ifndef SKYLIB_STATE_MANAGER_H_
#define SKYLIB_STATE_MANAGER_H_

#include <skylib/state.h>

namespace skylib {

class StateManager {
 public:
  StateManager();

  void SetState(State *state);
  void ClearState();
  void Update() const;
  void Draw() const;

 private:
  State *state_;
  bool state_valid_;
};

} // namespace skylib

#endif // SKYLIB_STATE_MANAGER_H_
