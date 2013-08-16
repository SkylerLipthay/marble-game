#include <skylib/vertex/vertex.h>
#include <GL/gl.h>

namespace skylib {

Vertex::Vertex() {
}

Vertex::Vertex(Vector<3> vertex) : vertex_(vertex) {
}

void Vertex::DrawBatch(Vertex *batch,
                       unsigned int count) {
  glEnableClientState(GL_VERTEX_ARRAY);

  static const unsigned int size = sizeof(Vertex);
  const float *batch_data = reinterpret_cast<float *>(batch);

  glVertexPointer(3, GL_FLOAT, size, batch_data + kVertexOffset);

  glDrawArrays(GL_TRIANGLES, 0, count);

  glDisableClientState(GL_VERTEX_ARRAY);
}

} // namespace skylib
