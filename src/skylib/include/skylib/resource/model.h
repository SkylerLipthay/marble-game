#ifndef SKYLIB_RESOURCE_MODEL_H_
#define SKYLIB_RESOURCE_MODEL_H_

#include <skylib/resource/resource.h>
#include <skylib/math/matrix.h>
#include <btBulletDynamicsCommon.h>
#include <iostream>

namespace skylib {

class Model : virtual public Resource {
 public:
  Model();
  ~Model();

  bool Load(std::istream& stream);
  bool Unload();
  bool IsLoaded() const;
  void Render() const;
  void Render(Matrix<4, 4> const& transformations) const;
  btTriangleMesh *GetTriangleMesh();

 private:
  enum VertexType {
    kVertex,
    kVertexColor,
    kVertexNormal,
    kVertexNormalColor,
    kVertexNormalTexture,
    kVertexTexture
  };

  bool loaded_;
  void *buffer_;
  VertexType buffer_type_;
  unsigned int buffer_size_;
  btTriangleMesh triangle_mesh_;
};

} // namespace skylib

#endif // SKYLIB_RESOURCE_MODEL_H_
