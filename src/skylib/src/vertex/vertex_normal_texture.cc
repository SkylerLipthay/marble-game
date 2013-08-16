#include <skylib/vertex/vertex_normal_texture.h>
#include <GL/gl.h>

namespace skylib {

VertexNormalTexture::VertexNormalTexture() {
}

VertexNormalTexture::VertexNormalTexture(Vector<3> vertex,
                                         Vector<3> normal,
                                         Vector<2> texture_coords)
    : texture_coords_(texture_coords),
      normal_(normal),
      vertex_(vertex) {
}

void VertexNormalTexture::DrawBatch(VertexNormalTexture *batch,
                                    unsigned int count) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  static const unsigned int size = sizeof(VertexNormalTexture);
  const float *batch_data = reinterpret_cast<float *>(batch);

  glTexCoordPointer(2, GL_FLOAT, size, batch_data + kTextureCoordsOffset);
  glNormalPointer(GL_FLOAT, size, batch_data + kNormalOffset);
  glVertexPointer(3, GL_FLOAT, size, batch_data + kVertexOffset);

  glDrawArrays(GL_TRIANGLES, 0, count);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

} // namespace skylib
