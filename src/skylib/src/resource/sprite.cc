#include <skylib/resource/sprite.h>

namespace skylib {

Sprite::Sprite(Texture const& texture) {
  texture_ = &texture;
  initialized_ = false;
}

Sprite::~Sprite() {
  if (!initialized_) {
    return;
  }

  delete[] buffer_;
}

bool Sprite::Initialize() {
  if (initialized_) {
    return false;
  }

  if (!texture_->IsLoaded()) {
    return false;
  }

  return Initialize(texture_->GetWidth(), texture_->GetHeight());
}

bool Sprite::Initialize(int width, int height, int x1, int x2, int y1, int y2) {
  if (initialized_) {
    return false;
  }

  if (!texture_->IsLoaded()) {
    return false;
  }

  Vector<2> coord[4];

  if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
    coord[0] = Vector<2>(0, 1);
    coord[1] = Vector<2>(1, 1);
    coord[2] = Vector<2>(0, 0);
    coord[3] = Vector<2>(1, 0);
  } else {
    const int t_width = texture_->GetWidth();
    const int t_height = texture_->GetHeight();
    coord[0] = Vector<2>(static_cast<float>(x1) / static_cast<float>(t_width),
                         static_cast<float>(y2) / static_cast<float>(t_height));
    coord[1] = Vector<2>(static_cast<float>(x2) / static_cast<float>(t_width),
                         static_cast<float>(y2) / static_cast<float>(t_height));
    coord[2] = Vector<2>(static_cast<float>(x1) / static_cast<float>(t_width),
                         static_cast<float>(y1) / static_cast<float>(t_height));
    coord[3] = Vector<2>(static_cast<float>(x2) / static_cast<float>(t_width),
                         static_cast<float>(y1) / static_cast<float>(t_height));
  }

  buffer_ = new VertexTexture[6];
  buffer_[0] = VertexTexture(Vector<3>(0, 0, 0), coord[0]);
  buffer_[1] = VertexTexture(Vector<3>(width, 0, 0), coord[1]);
  buffer_[2] = VertexTexture(Vector<3>(0, height, 0), coord[2]);
  buffer_[3] = VertexTexture(Vector<3>(width, height, 0), coord[3]);
  buffer_[4] = buffer_[2];
  buffer_[5] = buffer_[1];

  initialized_ = true;
  
  return true;
}

void Sprite::BindTexture() const {
  if (!initialized_) {
    return;
  }

  texture_->Bind();
}

void Sprite::Render() const {
  if (!initialized_) {
    return;
  }
  
  VertexTexture::DrawBatch(buffer_, 6);
}

void Sprite::Render(Matrix<4, 4> const& transformations) const {
  glPushMatrix();
  glLoadMatrixf(transformations.Data());
  Render();
  glPopMatrix();
}

} // namespace skylib
