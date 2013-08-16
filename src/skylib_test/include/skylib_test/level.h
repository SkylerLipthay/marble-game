#ifndef SKYLIB_TEST_LEVEL_H_
#define SKYLIB_TEST_LEVEL_H_

#include <btBulletDynamicsCommon.h>
#include <string>
#include <vector>

namespace skylib_test {

struct LevelObject {
  LevelObject(std::string const& _model, btVector3 const& _position,
              const bool _goal, btQuaternion const& _rotation,
              const float _friction, const float _restitution) {
    model = _model;
    position = _position;
    goal = _goal;
    rotation = _rotation;
    friction = _friction;
    restitution = _restitution;
  }

  std::string model;
  btVector3 position;
  bool goal;
  btQuaternion rotation;
  float friction;
  float restitution;
};

class Level {
 public:
  Level(std::string const& path);

  const bool IsValid() const;
  std::string const& GetName() const;
  btVector3 const& GetSpawn() const;
  std::vector<LevelObject> const& GetObjects() const;

 private:
  bool valid_;
  std::string name_;
  btVector3 spawn_;
  std::vector<LevelObject> objects_;
};

} // namespace skylib_test

#endif // SKYLIB_TEST_LEVEL_H_
