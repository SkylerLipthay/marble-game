#ifndef SKYLIB_VERTEX_VERTEX_TEXTURE_H_
#define SKYLIB_VERTEX_VERTEX_TEXTURE_H_

#include <skylib/math/vector.h>

namespace skylib {

class VertexTexture {
 public:
  VertexTexture();
  VertexTexture(Vector<3> vertex, Vector<2> texture_coords);

  static void DrawBatch(VertexTexture *batch, unsigned int count);

 private:
  static const int kTextureCoordsOffset = 0;
  static const int kVertexOffset = kTextureCoordsOffset + 2;

  Vector<2> texture_coords_;
  Vector<3> vertex_;
};

} // namespace skylib

#endif // SKYLIB_VERTEX_VERTEX_TEXTURE_H_
