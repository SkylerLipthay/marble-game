#ifndef SKYLIB_TEST_TEST_STATE_H_
#define SKYLIB_TEST_TEST_STATE_H_

#include <skylib/state.h>
#include <skylib/engine.h>
#include <skylib/resource/model.h>
#include <skylib/resource/texture.h>
#include <skylib/resource/sprite.h>
#include <skylib_test/object.h>
#include <skylib_test/level.h>
#include <skylib_test/font.h>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include <string>

namespace skylib_test {

class TestState : virtual public skylib::State {
 public:
  TestState();
  ~TestState();

  static void NearCallback(btBroadphasePair& collisionPair,
                           btCollisionDispatcher& dispatcher,
                           btDispatcherInfo const& dispatchInfo);

  void Initialize(Level const& level, Font *font);
  void Update();
  void Draw();
  void UpdateCamera(int x, int y);
  void SetLeftActive(bool active);
  void SetRightActive(bool active);
  void SetUpActive(bool active);
  void SetDownActive(bool active);
  void Jump();
  void GoalHit();
  void Exit();
  const bool ShouldExit() const;

 private:
  skylib::Model *marble_;
  skylib::Model *table_;
  skylib::Model *goal_;
  skylib::Texture *texture_;
  skylib::Texture *shadow_;
  skylib::Texture *bert_;
  skylib::Sprite *shadow_sprite_;
  float rotation_x_;
  float rotation_y_;
  float velocity_x_;
  float velocity_z_;
  bool left_;
  bool right_;
  bool up_;
  bool down_;
  bool won_;
  btBroadphaseInterface *broadphase_;
  btCollisionConfiguration *collision_configuration_;
  btCollisionDispatcher *dispatcher_;
  btSequentialImpulseConstraintSolver *solver_;
  btDiscreteDynamicsWorld *dynamics_world_;
  btCollisionShape *fall_shape_;
  btRigidBody *fall_rigid_body_;
  std::vector<std::string> loaded_resources_;
  std::vector<Object *> objects_;
  Font *font_;
  unsigned int tick_;
  unsigned int won_tick_;
  bool exit_;
};

} // namespace skylib_test

#endif // SKYLIB_TEST_TEST_STATE_H_
