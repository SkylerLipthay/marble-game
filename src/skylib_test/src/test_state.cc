#include <skylib_test/test_state.h>
#include <skylib/math/matrix.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <GL/gl.h>

namespace skylib_test {

void TestState::NearCallback(btBroadphasePair& collisionPair,
                             btCollisionDispatcher& dispatcher,
                             btDispatcherInfo const& dispatchInfo) {
  btBroadphaseProxy *proxy0 = collisionPair.m_pProxy0;
  btBroadphaseProxy *proxy1 = collisionPair.m_pProxy1;
  btCollisionObject *object0 =
      reinterpret_cast<btCollisionObject *>(proxy0->m_clientObject);
  btCollisionObject *object1 =
      reinterpret_cast<btCollisionObject *>(proxy1->m_clientObject);
  TestState *parent = reinterpret_cast<TestState *>(object0->getUserPointer());
  btCollisionObject *ball = parent->fall_rigid_body_;

  if (object0 == ball || object1 == ball) {
    for (int index = 0; index < parent->objects_.size(); index++) {
      Object * const object = parent->objects_[index];
      if (!object->IsGoal()) {
        continue;
      }

      btRigidBody * const body = object->GetRigidBody();
      if (object0 == body || object1 == body) {
        parent->GoalHit();
      }
    }
  }

  dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);
}

TestState::TestState() {
  rotation_x_ = 0.0f;
  rotation_y_ = 0.0f;
  velocity_x_ = 0.0f;
  velocity_z_ = 0.0f;
  left_ = false;
  right_ = false;
  up_ = false;
  down_ = false;
  won_ = false;
  tick_ = 0;
  won_tick_ = 0;
  exit_ = false;
}

TestState::~TestState() {
  delete shadow_sprite_;

  for (int index = 0; index < loaded_resources_.size(); index++) {
    GetEngine().GetResourceManager().Unload(loaded_resources_[index]);
  }
  
  for (int index = 0; index < objects_.size(); index++) {
    delete objects_[index];
  }

  dynamics_world_->removeRigidBody(fall_rigid_body_);
  delete fall_rigid_body_->getMotionState();
  delete fall_rigid_body_;
  delete fall_shape_;
  delete dynamics_world_;
  delete solver_;
  delete collision_configuration_;
  delete dispatcher_;
  delete broadphase_;
}

void TestState::Initialize(Level const& level, Font *font) {
  font_ = font;

  std::ifstream file_marble;
  file_marble.open("res/marble.obj");
  GetEngine().GetResourceManager().Load("marble", file_marble, marble_);
  file_marble.close();
  loaded_resources_.push_back("marble");

  std::ifstream file_texture;
  file_texture.open("res/texture.png", std::ios::binary);
  GetEngine().GetResourceManager().Load("texture", file_texture, texture_);
  file_texture.close();
  loaded_resources_.push_back("texture");

  std::ifstream file_shadow;
  file_shadow.open("res/shadow.png", std::ios::binary);
  GetEngine().GetResourceManager().Load("shadow", file_shadow, shadow_);
  file_shadow.close();
  loaded_resources_.push_back("shadow");

  std::ifstream file_bert;
  file_bert.open("res/bert.png", std::ios::binary);
  GetEngine().GetResourceManager().Load("bert", file_bert, bert_);
  file_bert.close();
  loaded_resources_.push_back("bert");

  shadow_sprite_ = new skylib::Sprite(*shadow_);
  shadow_sprite_->Initialize(1, 1, 0, 63, 0, 63);

  broadphase_ = new btDbvtBroadphase();
  collision_configuration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collision_configuration_);
  solver_ = new btSequentialImpulseConstraintSolver();
  dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_, broadphase_,
                                                solver_,
                                                collision_configuration_);
  dynamics_world_->setGravity(btVector3(0, -30.0f, 0));

  fall_shape_ = new btSphereShape(0.5f);
  btDefaultMotionState *fall_motion_state = new btDefaultMotionState(
      btTransform(btQuaternion(0, 0, 0, 1.0f), level.GetSpawn()));
  btScalar mass = 1.0f;
  btVector3 fall_inertia(0, 0, 0);
  fall_shape_->calculateLocalInertia(mass, fall_inertia);
  btRigidBody::btRigidBodyConstructionInfo fall_rigid_body_ci(
      mass, fall_motion_state, fall_shape_, fall_inertia);
  fall_rigid_body_ci.m_friction = 2.0f;
  fall_rigid_body_ci.m_restitution = 0.4f;
  fall_rigid_body_ = new btRigidBody(fall_rigid_body_ci);
  fall_rigid_body_->setAngularFactor(1.0f);
  fall_rigid_body_->setActivationState(DISABLE_DEACTIVATION);
  fall_rigid_body_->setDamping(0.5f, 0.925f);
  fall_rigid_body_->setUserPointer(this);
  dynamics_world_->addRigidBody(fall_rigid_body_);

  dispatcher_->setNearCallback(TestState::NearCallback);

  for (int index = 0; index < level.GetObjects().size(); index++) {
    LevelObject const& level_object = level.GetObjects().at(index);
    skylib::Model *model;
    std::string const& resource_name = "__" + level_object.model;

    const bool resource_exists = GetEngine().GetResourceManager().GetResource(
        resource_name, model);

    if (!resource_exists) {
      std::ifstream file;
      file.open(std::string("res/" + level_object.model).c_str(),
                std::ios::binary);
      GetEngine().GetResourceManager().Load(resource_name, file, model);
      file.close();
      loaded_resources_.push_back(resource_name);
    }

    Object *object = new Object(model, dynamics_world_, level_object.goal, this,
                                level_object.position, level_object.rotation,
                                level_object.friction,
                                level_object.restitution);
    objects_.push_back(object);
  }

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  float ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}

void TestState::Update() {
  btVector3 accel = btVector3((up_ ? 8.5 : 0) + (down_ ? -8.5 : 0),
                              0,
                              (right_ ? 8.5 : 0) + (left_ ? -8.5 : 0));
  accel = accel.rotate(btVector3(0, 1, 0), rotation_y_ * -0.0174532925f);

  fall_rigid_body_->applyTorque(accel);

  btVector3 force = btVector3((left_ ? 8.5 : 0) + (right_ ? -8.5 : 0),
                              0,
                              (up_ ? 8.5 : 0) + (down_ ? -8.5 : 0));
  force = force.rotate(btVector3(0, 1, 0), rotation_y_ * -0.0174532925f);
  fall_rigid_body_->applyCentralForce(force);

  if (fall_rigid_body_->getWorldTransform().getOrigin().getY() < -10.0f) {
    fall_rigid_body_->setLinearVelocity(btVector3(0, 0, 0));
    fall_rigid_body_->setAngularVelocity(btVector3(0, 0, 0));
    fall_rigid_body_->getWorldTransform().setIdentity();
    fall_rigid_body_->getWorldTransform().setOrigin(btVector3(0, 0.5f, 0));
    tick_ = 0;
  }

  if (!won_) {
    dynamics_world_->stepSimulation(1.0f / 60.0f, 10);
    tick_++;
  } else {
    won_tick_++;
    if (won_tick_ > 120) {
      exit_ = true;
    }
  }
}

void TestState::Draw() {
  glEnable(GL_LIGHTING);
  glBindTexture(GL_TEXTURE_2D, 0);

  GetEngine().SetClearColor(skylib::Color::Blue());
  GetEngine().Clear();

  GetEngine().SetProjectionPerspective(45.0f, 0.1f, 10000.0f);

  skylib::Transform matrix = skylib::Transform::RotateY(rotation_y_);
  matrix = matrix * skylib::Transform::RotateX(rotation_x_);
  matrix = matrix * skylib::Transform::Translate(0.0f, -1.5f, -10.0f);

  glLoadMatrixf(matrix.Data());
  float position[] = { 0.0f, 10000.0f, 0.0f, 1 };
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  btTransform pos;
  fall_rigid_body_->getMotionState()->getWorldTransform(pos);

  glPushMatrix();
  // marble always centered
  texture_->Bind();
  float mat[16];
  pos.setOrigin(btVector3(0, 0, 0));
  pos.getOpenGLMatrix(mat);
  glMultMatrixf(skylib::Transform::RotateY(180.0f).Data());
  glMultMatrixf(mat);
  marble_->Render();
  glPopMatrix();

  glPushMatrix();

  fall_rigid_body_->getMotionState()->getWorldTransform(pos);
  glMultMatrixf(skylib::Transform::Translate(pos.getOrigin().getX(),
                                             -pos.getOrigin().getY(),
                                             pos.getOrigin().getZ()).Data());

  bert_->Bind();

  for (int index = 0; index < objects_.size(); index++) {
    Object * const object = objects_[index];
    object->Draw();
  }

  glPopMatrix();

  btVector3 ball = pos.getOrigin();
  float y = ball.getY();
  ball.setY(y);
  btVector3 end = ball;
  end.setY(y - 1000.0f);

  btCollisionWorld::ClosestRayResultCallback ray_callback(ball, end);
  dynamics_world_->rayTest(ball, end, ray_callback);

  shadow_->Bind();
  if (ray_callback.hasHit()) {
    end = ray_callback.m_hitPointWorld;
    const float dist = y - end.getY();
    btVector3 normal = ray_callback.m_hitNormalWorld;
    normal.normalize();
    btVector3 old_normal(0, 1, 0);
    btVector3 axis = old_normal.cross(normal);
    float angle = std::acos(old_normal.dot(normal)) * -57.2957795f;

    matrix = skylib::Transform::RotateX(270.0f);
    matrix = matrix * skylib::Transform::Translate(-0.5f, 0, 0.5f);
    glPushMatrix();
    glMultMatrixf(skylib::Transform::Translate(0, -(dist - 0.05f), 0).Data());
    if (axis.length() > 0.01f) {
      glRotatef(angle, axis.getX(), axis.getY(), axis.getZ());
    }
    glMultMatrixf(matrix.Data());
    shadow_sprite_->Render();
    glPopMatrix();
  }

  glDisable(GL_LIGHTING);
  const int height = GetEngine().SetProjectionParallel(1500, -1.0f, 1.0f);
  glLoadIdentity();
  font_->Bind();

  const float seconds = tick_ / 60.0f;
  const int new_seconds = static_cast<int>(seconds);
  const int milliseconds = (seconds - new_seconds) * 100;
  const int minutes = new_seconds / 60;
  const int newest_seconds = new_seconds % 60;

  std::ostringstream time;
  time << std::setfill('0') << std::setw(1);
  time << minutes << ":";
  time << std::setfill('0') << std::setw(2);
  time << newest_seconds << ".";
  time << std::setfill('0') << std::setw(2);
  time << milliseconds;

  font_->Draw(time.str(), 16, height - 88);

  if (won_) {
    font_->Draw("Great job!", 605, height / 2 - 40);
  }
}

void TestState::UpdateCamera(int x, int y) {
  rotation_y_ += x;
  rotation_x_ -= y;

  while (rotation_y_ >= 360.0f) {
    rotation_y_ -= 360.0f;
  }

  while (rotation_y_ < 0.0f) {
    rotation_y_ += 360.0f;
  }

  if (rotation_x_ > 90.0f) {
    rotation_x_ = 90.0f;
  }

  if (rotation_x_ < 0.0f) {
    rotation_x_ = 0.0f;
  }
}

void TestState::SetLeftActive(bool active) {
  left_ = active;
}

void TestState::SetRightActive(bool active) {
  right_ = active;
}

void TestState::SetUpActive(bool active) {
  up_ = active;
}

void TestState::SetDownActive(bool active) {
  down_ = active;
}

void TestState::Jump() {
  btTransform pos;
  fall_rigid_body_->getMotionState()->getWorldTransform(pos);
  btVector3 ball = pos.getOrigin();
  float y = ball.getY();
  ball.setY(y);
  btVector3 end = ball;
  end.setY(y - 1.0f);

  btCollisionWorld::ClosestRayResultCallback ray_callback(ball, end);
  dynamics_world_->rayTest(ball, end, ray_callback);

  if (ray_callback.hasHit()) {
    fall_rigid_body_->applyCentralImpulse(btVector3(0, 16, 0));
  }
}

void TestState::Exit() {
  exit_ = true;
}

void TestState::GoalHit() {
  won_ = true;
}

const bool TestState::ShouldExit() const {
  return exit_;
}

} // namespace skylib_test
