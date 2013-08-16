#ifndef SKYLIB_VERTEX_VERTEX_NORMAL_H_
#define SKYLIB_VERTEX_VERTEX_NORMAL_H_

#include <skylib/math/vector.h>
#include <skylib/common/color.h>

namespace skylib {

class VertexNormal {
 public:
  VertexNormal();
  VertexNormal(Vector<3> vertex, Vector<3> normal);

  static void DrawBatch(VertexNormal *batch, unsigned int count);

 private:
  static const int kNormalOffset = 0;
  static const int kVertexOffset = kNormalOffset + 3;

  Vector<3> normal_;
  Vector<3> vertex_;
};

} // namespace skylib

#endif // SKYLIB_VERTEX_VERTEX_NORMAL_H_
