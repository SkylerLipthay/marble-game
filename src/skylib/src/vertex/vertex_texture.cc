#include <skylib/vertex/vertex_texture.h>
#include <GL/gl.h>

namespace skylib {

VertexTexture::VertexTexture() {
}

VertexTexture::VertexTexture(Vector<3> vertex, Vector<2> texture_coords)
    : texture_coords_(texture_coords),
      vertex_(vertex) {
}

void VertexTexture::DrawBatch(VertexTexture *batch, unsigned int count) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  static const unsigned int size = sizeof(VertexTexture);
  const float *batch_data = reinterpret_cast<float *>(batch);

  glTexCoordPointer(2, GL_FLOAT, size, batch_data + kTextureCoordsOffset);
  glVertexPointer(3, GL_FLOAT, size, batch_data + kVertexOffset);

  glDrawArrays(GL_TRIANGLES, 0, count);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

} // namespace skylib
