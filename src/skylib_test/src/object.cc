#include <skylib_test/object.h>
#include <GL/gl.h>

namespace skylib_test {

static skylib::Transform physics_rotation = skylib::Transform::RotateY(180.0f);
static float physics_matrix[16];
static btTransform position;

Object::Object(skylib::Model *model, btDiscreteDynamicsWorld *world, bool goal,
               void *user_pointer, btVector3 position, btQuaternion rotation,
               float friction, float restitution) {
  model_ = model;
  world_ = world;
  goal_ = goal;

  shape_ = new btBvhTriangleMeshShape(model->GetTriangleMesh(), true);

  btDefaultMotionState *motion_state =
      new btDefaultMotionState(btTransform(rotation, position));
  btRigidBody::btRigidBodyConstructionInfo rigid_body_ci(0, motion_state,
                                                         shape_,
                                                         btVector3(0, 0, 0));
  rigid_body_ci.m_friction = friction;
  rigid_body_ci.m_restitution;
  rigid_body_ = new btRigidBody(rigid_body_ci);
  rigid_body_->setUserPointer(user_pointer);
  world_->addRigidBody(rigid_body_);
}

Object::~Object() {
  world_->removeRigidBody(rigid_body_);
  delete rigid_body_->getMotionState();
  delete rigid_body_;
  delete shape_;
}

void Object::Draw() const {
  glPushMatrix();
  rigid_body_->getMotionState()->getWorldTransform(position);
  position.getOpenGLMatrix(physics_matrix);
  glMultMatrixf(physics_rotation.Data());
  glMultMatrixf(physics_matrix);
  model_->Render();
  glPopMatrix();
}

btRigidBody *Object::GetRigidBody() {
  return rigid_body_;
}

const bool Object::IsGoal() const {
  return goal_;
}


} // namepspace skylib_test
