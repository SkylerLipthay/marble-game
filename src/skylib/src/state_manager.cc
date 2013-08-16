#include <skylib/state_manager.h>

namespace skylib {

StateManager::StateManager() {
  state_valid_ = false;
}

void StateManager::SetState(State *state) {
  state_ = state;
  state_valid_ = true;
}

void StateManager::ClearState() {
  state_valid_ = false;
}

void StateManager::Update() const {
  if (!state_valid_) {
    return;
  }

  state_->Update();
}

void StateManager::Draw() const {
  if (!state_valid_) {
    return;
  }

  state_->Draw();
}

} // namespace skylib
