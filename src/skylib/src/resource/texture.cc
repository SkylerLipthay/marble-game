#include <skylib/resource/texture.h>
#include <skylib/resource/stb_image.h>

namespace skylib {

Texture::Texture() {
  loaded_ = false;
}

Texture::~Texture() {
  Unload();
}

bool Texture::Unload() {
  if (!loaded_) {
    return false;
  }

  glDeleteTextures(1, &name_);

  loaded_ = false;

  return true;
}

bool Texture::Load(std::istream& stream) {
  if (loaded_) {
    return false;
  }

  stream.seekg(0, std::ios::end);
  unsigned int length = stream.tellg();
  stream.seekg(0, std::ios::beg);

  char *file_buffer = new char[length];
  stream.read(file_buffer, length);

  stbi_uc *image_data = stbi_load_from_memory(
      reinterpret_cast<const stbi_uc *>(file_buffer),
      length, &width_, &height_, &components_, STBI_rgb_alpha);

  glGenTextures(1, &name_);
  glBindTexture(GL_TEXTURE_2D, name_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  stbi_image_free(image_data);

  delete[] file_buffer;

  loaded_ = true;

  return true;
}

bool Texture::IsLoaded() const {
  return loaded_;
}

void Texture::Bind() const {
  glBindTexture(GL_TEXTURE_2D, name_);
}

const int Texture::GetWidth() const {
  return width_;
}

const int Texture::GetHeight() const {
  return height_;
}

} // namespace skylib
