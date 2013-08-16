#include <skylib/vertex/vertex_color.h>
#include <GL/gl.h>

namespace skylib {

VertexColor::VertexColor() {
}

VertexColor::VertexColor(Vector<3> vertex, Color color)
    : color_(color),
      vertex_(vertex) {
}

void VertexColor::DrawBatch(VertexColor *batch, unsigned int count) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  static const unsigned int size = sizeof(VertexColor);
  const float *batch_data = reinterpret_cast<float *>(batch);

  glColorPointer(4, GL_FLOAT, size, batch_data + kColorOffset);
  glVertexPointer(3, GL_FLOAT, size, batch_data + kVertexOffset);

  glDrawArrays(GL_TRIANGLES, 0, count);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

} // namespace skylib
