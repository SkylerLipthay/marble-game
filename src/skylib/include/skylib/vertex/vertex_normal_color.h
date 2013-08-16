#ifndef SKYLIB_VERTEX_VERTEX_NORMAL_COLOR_H_
#define SKYLIB_VERTEX_VERTEX_NORMAL_COLOR_H_

#include <skylib/math/vector.h>
#include <skylib/common/color.h>

namespace skylib {

class VertexNormalColor {
 public:
  VertexNormalColor();
  VertexNormalColor(Vector<3> vertex, Vector<3> normal, Color color);

  static void DrawBatch(VertexNormalColor *batch, unsigned int count);

 private:
  static const int kColorOffset = 0;
  static const int kNormalOffset = kColorOffset + 4;
  static const int kVertexOffset = kNormalOffset + 3;

  Color color_;
  Vector<3> normal_;
  Vector<3> vertex_;
};

} // namespace skylib

#endif // SKYLIB_VERTEX_VERTEX_NORMAL_COLOR_H_
