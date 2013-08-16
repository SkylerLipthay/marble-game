#ifndef SKYLIB_TEST_OBJECT_H_
#define SKYLIB_TEST_OBJECT_H_

#include <skylib/resource/model.h>
#include <skylib/resource/texture.h>
#include <btBulletDynamicsCommon.h>

namespace skylib_test {

class Object {
 public:
  Object(skylib::Model *model, btDiscreteDynamicsWorld *world, bool goal,
         void *user_pointer, btVector3 position,
         btQuaternion rotation = btQuaternion(0, 0, 0, 1.0f),
         float friction = 2.0f, float restitution = 0.4f);
  ~Object();

  void Draw() const;
  btRigidBody *GetRigidBody();
  const bool IsGoal() const;

 private:
  skylib::Model *model_;
  btCollisionShape *shape_;
  btRigidBody *rigid_body_;
  btDiscreteDynamicsWorld *world_;
  bool goal_;
};

} // namespace skylib_test

#endif // SKYLIB_TEST_OBJECT_H_
