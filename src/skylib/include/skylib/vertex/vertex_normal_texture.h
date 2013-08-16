#ifndef SKYLIB_VERTEX_VERTEX_NORMAL_TEXTURE_H_
#define SKYLIB_VERTEX_VERTEX_NORMAL_TEXTURE_H_

#include <skylib/math/vector.h>

namespace skylib {

class VertexNormalTexture {
 public:
  VertexNormalTexture();
  VertexNormalTexture(Vector<3> vertex, Vector<3> normal,
                      Vector<2> texture_coords);

  static void DrawBatch(VertexNormalTexture *batch, unsigned int count);

 private:
  static const int kTextureCoordsOffset = 0;
  static const int kNormalOffset = kTextureCoordsOffset + 2;
  static const int kVertexOffset = kNormalOffset + 3;

  Vector<2> texture_coords_;
  Vector<3> normal_;
  Vector<3> vertex_;
};

} // namespace skylib

#endif // SKYLIB_VERTEX_VERTEX_NORMAL_TEXTURE_H_
