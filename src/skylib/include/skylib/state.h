#ifndef SKYLIB_STATE_H_
#define SKYLIB_STATE_H_

namespace skylib {

class Engine;

class State {
 public:
  virtual ~State();

  virtual void Update() = 0;
  virtual void Draw() = 0;
  void SetEngine(Engine *engine);
  Engine& GetEngine() const;

 private:
  Engine *engine_;
};

} // namespace skylib

#endif // SKYLIB_STATE_H_
