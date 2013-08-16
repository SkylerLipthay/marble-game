#include <skylib/vertex/vertex_normal.h>
#include <GL/gl.h>

namespace skylib {

VertexNormal::VertexNormal() {
}

VertexNormal::VertexNormal(Vector<3> vertex, Vector<3> normal)
    : normal_(normal),
      vertex_(vertex) {
}

void VertexNormal::DrawBatch(VertexNormal *batch, unsigned int count) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  static const unsigned int size = sizeof(VertexNormal);
  const float *batch_data = reinterpret_cast<float *>(batch);

  glNormalPointer(GL_FLOAT, size, batch_data + kNormalOffset);
  glVertexPointer(3, GL_FLOAT, size, batch_data + kVertexOffset);

  glDrawArrays(GL_TRIANGLES, 0, count);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}

} // namespace skylib
