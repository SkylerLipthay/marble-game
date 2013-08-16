#ifndef SKYLIB_VERTEX_VERTEX_COLOR_H_
#define SKYLIB_VERTEX_VERTEX_COLOR_H_

#include <skylib/math/vector.h>
#include <skylib/common/color.h>

namespace skylib {

class VertexColor {
 public:
  VertexColor();
  VertexColor(Vector<3> vertex, Color color);

  static void DrawBatch(VertexColor *batch, unsigned int count);

 private:
  static const int kColorOffset = 0;
  static const int kVertexOffset = kColorOffset + 4;

  Color color_;
  Vector<3> vertex_;
};

} // namespace skylib

#endif // SKYLIB_VERTEX_VERTEX_COLOR_H_
