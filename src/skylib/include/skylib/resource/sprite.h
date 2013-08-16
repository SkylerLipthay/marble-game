#ifndef SKYLIB_RESOURCE_SPRITE_H_
#define SKYLIB_RESOURCE_SPRITE_H_

#include <skylib/resource/texture.h>
#include <skylib/vertex/vertex_texture.h>
#include <skylib/math/matrix.h>

namespace skylib {

class Sprite {
 public:
  Sprite(Texture const& texture);
  ~Sprite();

  bool Initialize();
  bool Initialize(int width, int height, int x1 = -1, int x2 = -1, int y1 = -1,
                  int y2 = -1);
  void BindTexture() const;
  void Render() const;
  void Render(Matrix<4, 4> const& transformations) const;

 private:
  const Texture *texture_;
  bool initialized_;
  VertexTexture *buffer_;
};

} // namespace skylib

#endif // SKYLIB_RESOURCE_SPRITE_H_
