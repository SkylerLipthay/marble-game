#include <skylib/vertex/vertex_normal_color.h>
#include <GL/gl.h>

namespace skylib {

VertexNormalColor::VertexNormalColor() {
}

VertexNormalColor::VertexNormalColor(Vector<3> vertex, Vector<3> normal,
                                     Color color)
    : color_(color),
      normal_(normal),
      vertex_(vertex) {
}

void VertexNormalColor::DrawBatch(VertexNormalColor *batch,
                                  unsigned int count) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  static const unsigned int size = sizeof(VertexNormalColor);
  const float *batch_data = reinterpret_cast<float *>(batch);

  glColorPointer(4, GL_FLOAT, size, batch_data + kColorOffset);
  glNormalPointer(GL_FLOAT, size, batch_data + kNormalOffset);
  glVertexPointer(3, GL_FLOAT, size, batch_data + kVertexOffset);

  glDrawArrays(GL_TRIANGLES, 0, count);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

} // namespace skylib
