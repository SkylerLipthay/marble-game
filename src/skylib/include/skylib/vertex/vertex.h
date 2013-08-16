#ifndef SKYLIB_VERTEX_VERTEX_H_
#define SKYLIB_VERTEX_VERTEX_H_

#include <skylib/math/vector.h>

namespace skylib {

class Vertex {
 public:
  Vertex();
  Vertex(Vector<3> vertex_);

  static void DrawBatch(Vertex *batch, unsigned int count);

 private:
  static const int kVertexOffset = 0;

  Vector<3> vertex_;
};

} // namespace skylib

#endif // SKYLIB_VERTEX_VERTEX_H_
