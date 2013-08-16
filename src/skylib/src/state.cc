#include <skylib/state.h>

namespace skylib {

State::~State() {
}

void State::SetEngine(Engine *engine) {
  engine_ = engine;
}

Engine& State::GetEngine() const {
  return *engine_;
}

} // namespace skylib
