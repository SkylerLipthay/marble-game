#ifndef SKYLIB_VERTEX_BATCH_H_
#define SKYLIB_VERTEX_BATCH_H_

namespace skylib {

template <typename T>
void DrawVertexBatch(T *batch, unsigned int count) {
  T::DrawBatch(batch, count);
}

} // namespace skylib

#endif // SKYLIB_VERTEX_BATCH_H_
